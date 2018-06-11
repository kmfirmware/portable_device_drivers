################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
portable_device_drivers.lss \

FLASH_IMAGE += \
portable_device_drivers.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: portable_device_drivers.elf secondary-outputs

# Tool invocations
portable_device_drivers.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,portable_device_drivers.map -mmcu=atmega2560 -o "portable_device_drivers.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

portable_device_drivers.lss: portable_device_drivers.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S portable_device_drivers.elf  >"portable_device_drivers.lss"
	@echo 'Finished building: $@'
	@echo ' '

portable_device_drivers.hex: portable_device_drivers.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex portable_device_drivers.elf  "portable_device_drivers.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: portable_device_drivers.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t portable_device_drivers.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: portable_device_drivers.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pm2560 -cstk600 -Pusb -Uflash:w:portable_device_drivers.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(FLASH_IMAGE)$(ELFS)$(LSS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) portable_device_drivers.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
