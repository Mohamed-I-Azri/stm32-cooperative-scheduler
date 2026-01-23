#include "Scheduler.hpp"
#include "VddTask.hpp"
#include "TempTask.hpp"
#include "CPULoadTask.hpp"
#include "ADCHelpers.hpp"
#include "stm32f4xx_hal.h"

// CubeMX ADC handle
extern ADC_HandleTypeDef hadc1;

// LED ports/pins per mapping
#define LED_VDD_PORT GPIOD
#define LED_VDD_PIN  GPIO_PIN_12

#define LED_TEMP_PORT GPIOD
#define LED_TEMP_PIN  GPIO_PIN_13

#define LED_CPULOAD_PORT GPIOD
#define LED_CPULOAD_PIN  GPIO_PIN_15

// Scheduler instance (static to keep lifetime)
static Scheduler* scheduler = nullptr;
static VddTask* vddTask = nullptr;
static TempTask* tempTask = nullptr;
static CPULoadTask* cpuTask = nullptr;

extern "C" void Scheduler_Init(void) {
    if (scheduler != nullptr) return; // already inited
    scheduler = new Scheduler(1000); // 1-second CPU window

    vddTask = new VddTask(&hadc1, LED_VDD_PORT, LED_VDD_PIN, 1000);
    tempTask = new TempTask(&hadc1, LED_TEMP_PORT, LED_TEMP_PIN, 1500);
    cpuTask = new CPULoadTask(scheduler, LED_CPULOAD_PORT, LED_CPULOAD_PIN, 500);

    scheduler->addTask(vddTask);
    scheduler->addTask(tempTask);
    scheduler->addTask(cpuTask);

    scheduler->initAll();
}

extern "C" void Scheduler_Run(void) {
    if (scheduler == nullptr) return;
    scheduler->runOnce();

}
