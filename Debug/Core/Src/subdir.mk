################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/ADCHelpers.cpp \
../Core/Src/CPULoadTask.cpp \
../Core/Src/Scheduler.cpp \
../Core/Src/SchedulerBridge.cpp \
../Core/Src/Task.cpp \
../Core/Src/TempTask.cpp \
../Core/Src/VddTask.cpp 

C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 

OBJS += \
./Core/Src/ADCHelpers.o \
./Core/Src/CPULoadTask.o \
./Core/Src/Scheduler.o \
./Core/Src/SchedulerBridge.o \
./Core/Src/Task.o \
./Core/Src/TempTask.o \
./Core/Src/VddTask.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

CPP_DEPS += \
./Core/Src/ADCHelpers.d \
./Core/Src/CPULoadTask.d \
./Core/Src/Scheduler.d \
./Core/Src/SchedulerBridge.d \
./Core/Src/Task.d \
./Core/Src/TempTask.d \
./Core/Src/VddTask.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADCHelpers.cyclo ./Core/Src/ADCHelpers.d ./Core/Src/ADCHelpers.o ./Core/Src/ADCHelpers.su ./Core/Src/CPULoadTask.cyclo ./Core/Src/CPULoadTask.d ./Core/Src/CPULoadTask.o ./Core/Src/CPULoadTask.su ./Core/Src/Scheduler.cyclo ./Core/Src/Scheduler.d ./Core/Src/Scheduler.o ./Core/Src/Scheduler.su ./Core/Src/SchedulerBridge.cyclo ./Core/Src/SchedulerBridge.d ./Core/Src/SchedulerBridge.o ./Core/Src/SchedulerBridge.su ./Core/Src/Task.cyclo ./Core/Src/Task.d ./Core/Src/Task.o ./Core/Src/Task.su ./Core/Src/TempTask.cyclo ./Core/Src/TempTask.d ./Core/Src/TempTask.o ./Core/Src/TempTask.su ./Core/Src/VddTask.cyclo ./Core/Src/VddTask.d ./Core/Src/VddTask.o ./Core/Src/VddTask.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

