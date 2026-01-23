#include "TempTask.hpp"
#include "stm32f4xx_hal.h"

// external hadc
extern ADC_HandleTypeDef hadc1;

TempTask::TempTask(ADC_HandleTypeDef* hadc_, GPIO_TypeDef* ledPort_, uint16_t ledPin_, uint32_t intervalMs_)
    : Task("Temp", intervalMs_, 1, ledPort_, ledPin_), hadc(hadc_) {}

void TempTask::init() {
    // nothing special
}

void TempTask::execute() {
    // read Vdda for improved accuracy (fallback if zero)
    float vdda = ADC_ReadVrefintVoltage(hadc);
    if (vdda <= 0.1f) vdda = 3.0f;
    float tempC = ADC_ReadTemperatureC(hadc, vdda);

    if (tempC < -100.0f || tempC > 200.0f) {
        // error reading
        ledPulseBlocking(120);
        HAL_Delay(380);
    } else {
        // map 20..80 C -> pulse 300..50 ms
        float minT = 20.0f, maxT = 80.0f;
        float t = tempC;
        if (t < minT) t = minT;
        if (t > maxT) t = maxT;
        float pct = (t - minT) / (maxT - minT);
        uint32_t pulse = 300 - (uint32_t)(pct * 250.0f); // 300 -> 50
        ledPulseBlocking(pulse);
    }
}
