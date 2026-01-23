#ifndef TEMPTASK_HPP
#define TEMPTASK_HPP

#include "Task.hpp"
#include "stm32f4xx_hal.h"
#include "ADCHelpers.hpp"

class TempTask : public Task {
public:
    TempTask(ADC_HandleTypeDef* hadc, GPIO_TypeDef* ledPort, uint16_t ledPin, uint32_t intervalMs = 1500);
    void init() override;
    void execute() override;
private:
    ADC_HandleTypeDef* hadc;
};

#endif // TEMPTASK_HPP
