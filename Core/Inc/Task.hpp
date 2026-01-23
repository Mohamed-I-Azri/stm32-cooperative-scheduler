#ifndef TASK_HPP
#define TASK_HPP

#include "stm32f4xx_hal.h"
#include <cstdint>

enum class TaskState {
    Idle,
    Begin,
    Executing
};

class Task {
public:
    Task(const char* name, uint32_t intervalMs, uint8_t priority,
         GPIO_TypeDef* ledPort, uint16_t ledPin);
    virtual ~Task() = default;

    // called by Scheduler; returns execution time in ms
    uint32_t runWrapper();

    virtual void execute() = 0;
    virtual void init() {}

    uint32_t getIntervalMs() const { return intervalMs; }
    uint8_t getPriority() const { return priority; }
    const char* getName() const { return name; }
    uint32_t nextRunAtMs = 0;

protected:
    void ledOn();
    void ledOff();
    void ledToggle();
    void ledPulseBlocking(uint32_t ms);

    const char* name;
    uint32_t intervalMs;
    uint8_t priority;
    TaskState state;

    GPIO_TypeDef* ledPort;
    uint16_t ledPin;
};

#endif // TASK_HPP
