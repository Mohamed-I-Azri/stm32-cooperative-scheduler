#ifndef VDDTASK_HPP
#define VDDTASK_HPP

#include "Task.hpp"
#include "stm32f4xx_hal.h"
#include "ADCHelpers.hpp"

class VddTask : public Task {
public:
    VddTask(ADC_HandleTypeDef* hadc, GPIO_TypeDef* ledPort, uint16_t ledPin, uint32_t intervalMs = 1000);
    void init() override;
    void execute() override;
    float getLastVdd() const { return lastVdd; }

private:
    ADC_HandleTypeDef* hadc;
    float lastVdd;
};

#endif // VDDTASK_HPP
