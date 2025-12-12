################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BUTTON.c \
../Core/Src/FSM_AUTO.c \
../Core/Src/FSM_ERROR.c \
../Core/Src/FSM_INIT.c \
../Core/Src/FSM_MANUAL.c \
../Core/Src/GLOBAL.c \
../Core/Src/LCD.c \
../Core/Src/SOFTWARE_TIMER.c \
../Core/Src/STATUS_LIGHT.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/BUTTON.o \
./Core/Src/FSM_AUTO.o \
./Core/Src/FSM_ERROR.o \
./Core/Src/FSM_INIT.o \
./Core/Src/FSM_MANUAL.o \
./Core/Src/GLOBAL.o \
./Core/Src/LCD.o \
./Core/Src/SOFTWARE_TIMER.o \
./Core/Src/STATUS_LIGHT.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/BUTTON.d \
./Core/Src/FSM_AUTO.d \
./Core/Src/FSM_ERROR.d \
./Core/Src/FSM_INIT.d \
./Core/Src/FSM_MANUAL.d \
./Core/Src/GLOBAL.d \
./Core/Src/LCD.d \
./Core/Src/SOFTWARE_TIMER.d \
./Core/Src/STATUS_LIGHT.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

