################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Part1Tokenizer.cpp \
../src/TestPart1.cpp 

CPP_DEPS += \
./src/Part1Tokenizer.d \
./src/TestPart1.d 

OBJS += \
./src/Part1Tokenizer.o \
./src/TestPart1.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Part1Tokenizer.d ./src/Part1Tokenizer.o ./src/TestPart1.d ./src/TestPart1.o

.PHONY: clean-src

