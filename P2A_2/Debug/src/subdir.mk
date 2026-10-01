################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/factorial.c \
../src/gpio_drv.c \
../src/log.c \
../src/main.c \
../src/riscv_uart.c 

C_DEPS += \
./src/factorial.d \
./src/gpio_drv.d \
./src/log.d \
./src/main.d \
./src/riscv_uart.d 

OBJS += \
./src/factorial.o \
./src/gpio_drv.o \
./src/log.o \
./src/main.o \
./src/riscv_uart.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	riscv-gaisler-elf-gcc -nostdlib -march=rv32im -mabi=ilp32 -I"/home/atcsol/eclipse-workspace/P2A_2/include" -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/factorial.d ./src/factorial.o ./src/gpio_drv.d ./src/gpio_drv.o ./src/log.d ./src/log.o ./src/main.d ./src/main.o ./src/riscv_uart.d ./src/riscv_uart.o

.PHONY: clean-src

