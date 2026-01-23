#include "CPULoadTask.hpp"
#include "stm32f4xx_hal.h"

CPULoadTask::CPULoadTask(Scheduler* sched_, GPIO_TypeDef* ledPort_, uint16_t ledPin_, uint32_t intervalMs_)
    : Task("CPULoad", intervalMs_, 0, ledPort_, ledPin_), scheduler(sched_) {}

void CPULoadTask::init() {
    // nothing
}

void CPULoadTask::execute() {
    float load = scheduler ? scheduler->getCpuLoadPercent() : 0.0f;
    if (load < 0.0f) load = 0.0f;
    if (load > 100.0f) load = 100.0f;

    // Map 0..100% to period 800..50 ms
    uint32_t period = 800 - (uint32_t)((load / 100.0f) * 750.0f);
    if (period < 50) period = 50;

    // blink once: half period on, half off
    ledOn();
    HAL_Delay(period / 2);
    ledOff();
    HAL_Delay(period / 2);
}
