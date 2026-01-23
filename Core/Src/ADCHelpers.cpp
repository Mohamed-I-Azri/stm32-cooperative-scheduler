#include "ADCHelpers.hpp"
#include "stm32f4xx_hal.h"

// Addresses from STM32F4 system memory for calibration constants
#define VREFINT_CAL_ADDR ((uint16_t*) ((uint32_t)0x1FFF7A2A))
#define TS_CAL1_ADDR     ((uint16_t*) ((uint32_t)0x1FFF7A2C)) // @30°C
#define TS_CAL2_ADDR     ((uint16_t*) ((uint32_t)0x1FFF7A2E)) // @110°C

// Extern ADC handle created by CubeMX generated code (in adc.c)
extern ADC_HandleTypeDef hadc1;

uint32_t ADC_ReadChannelRaw(ADC_HandleTypeDef* hadc, uint32_t channel) {
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    // For internal channels (temp, vrefint) HAL must have VREFINT / Temp sensor enabled by CubeMX
    HAL_ADC_ConfigChannel(hadc, &sConfig);

    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
    uint32_t raw = HAL_ADC_GetValue(hadc);
    HAL_ADC_Stop(hadc);
    return raw;
}

float ADC_ReadVrefintVoltage(ADC_HandleTypeDef* hadc) {
    uint32_t raw = ADC_ReadChannelRaw(hadc, ADC_CHANNEL_VREFINT);
    uint16_t vref_cal = *VREFINT_CAL_ADDR; // factory calibrated raw for Vrefint @ Vdda = 3.0V
    if (raw == 0 || vref_cal == 0) return 0.0f;
    // approximate Vdda
    float vdda = (3.0f * (float)vref_cal) / (float)raw;
    return vdda;
}

float ADC_ReadTemperatureC(ADC_HandleTypeDef* hadc, float vdda) {
    uint32_t raw = ADC_ReadChannelRaw(hadc, ADC_CHANNEL_TEMPSENSOR);
    uint16_t ts_cal1 = *TS_CAL1_ADDR; // ADC raw at 30°C
    uint16_t ts_cal2 = *TS_CAL2_ADDR; // ADC raw at 110°C
    if (ts_cal1 == 0 || ts_cal2 == 0) return -273.15f;

    // use linear interpolation based on ADC counts
    // Temperature = 30 + (raw - ts_cal1) * (110 - 30) / (ts_cal2 - ts_cal1)
    float temp = 30.0f + ((float)(raw - ts_cal1)) * (80.0f / (float)(ts_cal2 - ts_cal1));
    (void)vdda; // not used directly here; could be used for more accurate conversion
    return temp;
}
