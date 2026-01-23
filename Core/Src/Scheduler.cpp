#include "Scheduler.hpp"
#include "stm32f4xx_hal.h"
#include <algorithm>

Scheduler::Scheduler(uint32_t cpuWindowMs_)
    : cpuWindowMs(cpuWindowMs_), windowStartMs(HAL_GetTick()),
      accumulatedTaskMs(0), idleCounter(0) {}

Scheduler::~Scheduler() {
    tasks.clear();
}

void Scheduler::addTask(Task* t) {
    if (!t) return;
    tasks.push_back(t);
    t->nextRunAtMs = HAL_GetTick() + t->getIntervalMs();
}

void Scheduler::initAll() {
    for (auto t : tasks) {
        if (t) {
            t->init();
            t->nextRunAtMs = HAL_GetTick() + t->getIntervalMs();
        }
    }
}

void Scheduler::countIdle() {
    idleCounter++;
}

float Scheduler::getCpuLoadPercent() const {
    if (cpuWindowMs == 0) return 0.0f;
    float pct = (100.0f * (float)accumulatedTaskMs) / (float)cpuWindowMs;
    if (pct < 0.0f) pct = 0.0f;
    if (pct > 100.0f) pct = 100.0f;
    return pct;
}

void Scheduler::runOnce() {
    uint32_t now = HAL_GetTick();

    // sort by priority high->low
    std::sort(tasks.begin(), tasks.end(), [](Task* a, Task* b){
        return a->getPriority() > b->getPriority();
    });

    for (Task* t : tasks) {
        if (t == nullptr) continue;
        if (now >= t->nextRunAtMs) {
            uint32_t execMs = t->runWrapper();
            accumulatedTaskMs += execMs;
            t->nextRunAtMs = now + t->getIntervalMs();
        }
    }

    // reset window if expired
    if ((now - windowStartMs) >= cpuWindowMs) {
        windowStartMs = now;
        accumulatedTaskMs = 0;
        idleCounter = 0;
    }
}
