# stm32-cooperative-scheduler

A bare-metal cooperative task scheduler for the STM32F407-Discovery, written in C++.
Designed around an object-oriented architecture — not an RTOS, no dynamic context switching.
Tasks are plain C++ objects; the scheduler owns them and dispatches them by priority on each cycle.

## Architecture

### `Task` (abstract base class)
- Stores interval, priority, execution state, and an LED port/pin
- `runWrapper()` calls `execute()`, measures wall-clock time via `HAL_GetTick()`, and returns elapsed ms to the scheduler
- LED helpers (`ledOn`, `ledOff`, `ledPulseBlocking`) available to all derived tasks
- Concrete tasks inherit and override only `execute()`

### `Scheduler`
- Owns a `std::vector<Task*>`
- Each call to `runOnce()` dispatches any task whose deadline has elapsed, sorted by priority (high → low)
- Accumulates per-task execution time against a configurable rolling window to compute CPU load %

### Concrete Tasks

| Class | LED | Interval | What it measures |
|---|---|---|---|
| `VddTask` | PD12 | 1000 ms | Supply voltage via Vrefint ADC channel |
| `TempTask` | PD13 | 1500 ms | Die temperature via internal sensor |
| `CPULoadTask` | PD15 | 500 ms | Scheduler CPU utilisation % |

### LED Encoding
Each task encodes its measured value as a pulse width on its assigned LED:

- **VddTask** — 2.5 V → 350 ms pulse, 3.6 V → 50 ms pulse
- **TempTask** — 20 °C → 300 ms pulse, 80 °C → 50 ms pulse
- **CPULoadTask** — 0 % → 800 ms blink period, 100 % → 50 ms blink period

### ADC Calibration
Raw ADC readings are corrected using factory-programmed constants from STM32 system memory:

| Constant | Address | Description |
|---|---|---|
| `VREFINT_CAL` | `0x1FFF7A2A` | Vrefint raw count @ Vdda = 3.0 V |
| `TS_CAL1` | `0x1FFF7A2C` | Temperature sensor raw count @ 30 °C |
| `TS_CAL2` | `0x1FFF7A2E` | Temperature sensor raw count @ 110 °C |

Vdda is back-calculated from Vrefint on every cycle and passed to the temperature task for improved accuracy.

### C / C++ Bridge
`Scheduler_Init()` and `Scheduler_Run()` are exposed with `extern "C"` linkage,
allowing the CubeMX-generated `main.c` to call into the C++ object graph without modification.

## Hardware

- **Board:** STM32F407-Discovery
- **MCU:** STM32F407VG (Cortex-M4, 16 MHz HSI, no PLL)
- **LEDs:** PD12, PD13, PD14, PD15
- **Button:** PA0 (configured, reserved for future use)
- **ADC:** ADC1, software-triggered, 12-bit, internal channels only

## Build

Developed with **STM32CubeIDE**. Clone the repo and import as an existing project.
Requires the STM32F4 HAL and a C++11-capable ARM toolchain.

## Known Limitations

- Tasks use `HAL_Delay()` inside `execute()` for LED timing — this blocks the scheduler
  and inflates the CPU load metric. A non-blocking timer approach would be the correct fix.
- `std::sort` runs on every scheduler cycle; since priorities are static, sorting once at
  `addTask()` time would be sufficient.
- `MX_ADC1_Init()` is called after `Scheduler_Init()` in `main.c` — this is an initialisation
  order issue inherited from CubeMX code generation and should be corrected.
