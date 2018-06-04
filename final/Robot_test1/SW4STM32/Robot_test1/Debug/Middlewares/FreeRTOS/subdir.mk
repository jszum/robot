################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/list.c \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

OBJS += \
./Middlewares/FreeRTOS/cmsis_os.o \
./Middlewares/FreeRTOS/croutine.o \
./Middlewares/FreeRTOS/event_groups.o \
./Middlewares/FreeRTOS/heap_4.o \
./Middlewares/FreeRTOS/list.o \
./Middlewares/FreeRTOS/port.o \
./Middlewares/FreeRTOS/queue.o \
./Middlewares/FreeRTOS/tasks.o \
./Middlewares/FreeRTOS/timers.o 

C_DEPS += \
./Middlewares/FreeRTOS/cmsis_os.d \
./Middlewares/FreeRTOS/croutine.d \
./Middlewares/FreeRTOS/event_groups.d \
./Middlewares/FreeRTOS/heap_4.d \
./Middlewares/FreeRTOS/list.d \
./Middlewares/FreeRTOS/port.d \
./Middlewares/FreeRTOS/queue.d \
./Middlewares/FreeRTOS/tasks.d \
./Middlewares/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/cmsis_os.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/cmsis_os.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/croutine.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/croutine.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/event_groups.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/event_groups.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/heap_4.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/heap_4.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/list.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/list.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/port.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/port.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/queue.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/queue.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/tasks.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/tasks.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/timers.o: E:/Politechnika\ Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -D__weak=__attribute__((weak)) -D__packed=__attribute__((__packed__)) -DUSE_HAL_DRIVER -DSTM32F072xB -I"E:/Politechnika Wroclawska/RTOS/robot/final/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/include" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"E:/Politechnika Wroclawska/RTOS/robot/final/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Middlewares/FreeRTOS/timers.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


