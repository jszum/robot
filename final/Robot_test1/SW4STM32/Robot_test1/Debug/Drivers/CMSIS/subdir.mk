################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Src/system_stm32f0xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f0xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f0xx.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Src/system_stm32f0xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Drivers/CMSIS/system_stm32f0xx.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


