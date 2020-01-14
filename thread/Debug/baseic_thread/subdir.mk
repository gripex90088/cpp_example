################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../baseic_thread/hellothread.c \
../baseic_thread/mutex.c \
../baseic_thread/pthread_create_join.c \
../baseic_thread/set_thread_attr.c \
../baseic_thread/thread_data.c \
../baseic_thread/thread_exit.c 

OBJS += \
./baseic_thread/hellothread.o \
./baseic_thread/mutex.o \
./baseic_thread/pthread_create_join.o \
./baseic_thread/set_thread_attr.o \
./baseic_thread/thread_data.o \
./baseic_thread/thread_exit.o 

C_DEPS += \
./baseic_thread/hellothread.d \
./baseic_thread/mutex.d \
./baseic_thread/pthread_create_join.d \
./baseic_thread/set_thread_attr.d \
./baseic_thread/thread_data.d \
./baseic_thread/thread_exit.d 


# Each subdirectory must supply rules for building sources it contributes
baseic_thread/%.o: ../baseic_thread/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


