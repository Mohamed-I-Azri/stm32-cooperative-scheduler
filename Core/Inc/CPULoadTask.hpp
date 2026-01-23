#ifndef CPULOADTASK_HPP
#define CPULOADTASK_HPP

#include "Task.hpp"
#include "stm32f4xx_hal.h"
#include "Scheduler.hpp"

class CPULoadTask : public Task {
public:
    CPULoadTask(Scheduler* sched, GPIO_TypeDef* ledPort, uint16_t ledPin, uint32_t intervalMs = 500);
    void init() override;
    void execute() override;

private:
    Scheduler* scheduler;
};

#endif // CPULOADTASK_HPP
