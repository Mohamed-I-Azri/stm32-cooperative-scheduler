#include "VddTask.hpp"
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1; // from adc.c

VddTask::VddTask(ADC_HandleTypeDef* hadc_, GPIO_TypeDef* ledPort_, uint16_t ledPin_, uint32_t intervalMs_)
    : Task("Vdd", intervalMs_, 2, ledPort_, ledPin_), hadc(hadc_), lastVdd(0.0f) {}

void VddTask::init() {
    // nothing extra
}

void VddTask::execute() {
    float v = ADC_ReadVrefintVoltage(hadc);
    lastVdd = v;

    // visualization: shorter pulse for higher V
    if (v <= 0.1f) {
        // error or read failure - blink slowly
        ledPulseBlocking(150);
        HAL_Delay(350);
    } else {
        // map range 2.5..3.6 -> pulse 350..50 ms
        float vmin = 2.5f, vmax = 3.6f;
        if (v < vmin) v = vmin;
        if (v > vmax) v = vmax;
        float pct = (v - vmin) / (vmax - vmin); // 0..1
        uint32_t pulse = 350 - (uint32_t)(pct * 300.0f); // 350..50
        ledPulseBlocking(pulse);
    }
}
