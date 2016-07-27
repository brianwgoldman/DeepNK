################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Configuration.cpp \
../src/DeepNK.cpp \
../src/Matrix.cpp \
../src/OutputNode.cpp \
../src/QualityMeasures.cpp \
../src/main.cpp 

OBJS += \
./src/Configuration.o \
./src/DeepNK.o \
./src/Matrix.o \
./src/OutputNode.o \
./src/QualityMeasures.o \
./src/main.o 

CPP_DEPS += \
./src/Configuration.d \
./src/DeepNK.d \
./src/Matrix.d \
./src/OutputNode.d \
./src/QualityMeasures.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -O0 -g3 -pg -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


