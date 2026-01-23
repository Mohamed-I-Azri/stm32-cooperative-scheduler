#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "Task.hpp"
#include <vector>
#include <cstdint>

class Scheduler {
public:
    Scheduler(uint32_t cpuWindowMs = 1000);
    ~Scheduler();

    void addTask(Task* t);
    void initAll();
    // run scheduler iteration
    void runOnce();

    // Called by main idle loops if you want to increment idle counter
    void countIdle();

    float getCpuLoadPercent() const;

private:
    std::vector<Task*> tasks;
    uint32_t cpuWindowMs;
    uint32_t windowStartMs;
    uint32_t accumulatedTaskMs; // ms of tasks executed in current window
    uint32_t idleCounter;
};

#endif // SCHEDULER_HPP
