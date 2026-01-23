#ifndef ADCHELPERS_HPP
#define ADCHELPERS_HPP

#include "stm32f4xx_hal.h"
#include <cstdint>

// Utility functions to read ADC internal channels (VREFINT, Temp sensor)
// These functions configure ADC channel on the fly and perform a single conversion.
// hadc must be ADC1 configured in CubeMX.

float ADC_ReadVrefintVoltage(ADC_HandleTypeDef* hadc); // returns Vdda in volts (approx)
uint32_t ADC_ReadChannelRaw(ADC_HandleTypeDef* hadc, uint32_t channel); // returns raw ADC 12-bit value
float ADC_ReadTemperatureC(ADC_HandleTypeDef* hadc, float vdda);

#endif // ADCHELPERS_HPP
