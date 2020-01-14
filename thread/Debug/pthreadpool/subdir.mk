################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pthreadpool/pthread_pool__simple.c \
../pthreadpool/pthreadpool_active.c 

OBJS += \
./pthreadpool/pthread_pool__simple.o \
./pthreadpool/pthreadpool_active.o 

C_DEPS += \
./pthreadpool/pthread_pool__simple.d \
./pthreadpool/pthreadpool_active.d 


# Each subdirectory must supply rules for building sources it contributes
pthreadpool/%.o: ../pthreadpool/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


