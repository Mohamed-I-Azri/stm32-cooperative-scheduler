#include "Task.hpp"
#include "stm32f4xx_hal.h"

Task::Task(const char* name_, uint32_t intervalMs_, uint8_t priority_,
           GPIO_TypeDef* ledPort_, uint16_t ledPin_)
    : name(name_), intervalMs(intervalMs_), priority(priority_), state(TaskState::Idle),
      ledPort(ledPort_), ledPin(ledPin_) {}

void Task::ledOn() { HAL_GPIO_WritePin(ledPort, ledPin, GPIO_PIN_SET); }
void Task::ledOff() { HAL_GPIO_WritePin(ledPort, ledPin, GPIO_PIN_RESET); }
void Task::ledToggle() { HAL_GPIO_TogglePin(ledPort, ledPin); }

void Task::ledPulseBlocking(uint32_t ms) {
    ledOn();
    HAL_Delay(ms);
    ledOff();
}

uint32_t Task::runWrapper() {
    state = TaskState::Begin;
    // LED solid on while about to begin
    ledOn();

    uint32_t t0 = HAL_GetTick();
    state = TaskState::Executing;

    // slight visible toggle to show execution (non-blocking)
    ledToggle();

    execute();

    uint32_t t1 = HAL_GetTick();
    uint32_t delta = (t1 >= t0) ? (t1 - t0) : 0;

    // indicate idle after execution
    ledOff();
    state = TaskState::Idle;
    return delta;
}
