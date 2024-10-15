################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/programes/Code composer/installation files/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./APP/APP.obj" \
"./FreeRTOS/Source/event_groups.obj" \
"./FreeRTOS/Source/list.obj" \
"./FreeRTOS/Source/queue.obj" \
"./FreeRTOS/Source/tasks.obj" \
"./FreeRTOS/Source/timers.obj" \
"./FreeRTOS/Source/portable/CCS/ARM_CM4F/port.obj" \
"./FreeRTOS/Source/portable/CCS/ARM_CM4F/portasm.obj" \
"./FreeRTOS/Source/portable/MemMang/heap_4.obj" \
"./HAL/LED.obj" \
"./HAL/Temperature_sensor.obj" \
"./HAL/pushbutton.obj" \
"./MCAL/ADC.obj" \
"./MCAL/GPIO.obj" \
"./MCAL/GPTM.obj" \
"./MCAL/NVIC.obj" \
"./MCAL/UART0.obj" \
"./MCAL/delay.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include APP/subdir_vars.mk
-include FreeRTOS/Source/subdir_vars.mk
-include FreeRTOS/Source/portable/CCS/ARM_CM4F/subdir_vars.mk
-include FreeRTOS/Source/portable/MemMang/subdir_vars.mk
-include HAL/subdir_vars.mk
-include MCAL/subdir_vars.mk
-include subdir_rules.mk
-include APP/subdir_rules.mk
-include FreeRTOS/Source/subdir_rules.mk
-include FreeRTOS/Source/portable/CCS/ARM_CM4F/subdir_rules.mk
-include FreeRTOS/Source/portable/MemMang/subdir_rules.mk
-include HAL/subdir_rules.mk
-include MCAL/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
SeatHeater_sysCtl.out 

EXE_OUTPUTS__QUOTED += \
"SeatHeater_sysCtl.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "SeatHeater_sysCtl.out"

# Tool invocations
SeatHeater_sysCtl.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"D:/programes/Code composer/installation files/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"SeatHeater_sysCtl.map" --heap_size=0 --stack_size=512 -i"D:/programes/Code composer/installation files/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" -i"D:/programes/Code composer/installation files/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="SeatHeater_sysCtl_linkInfo.xml" --rom_model -o "SeatHeater_sysCtl.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "APP\APP.obj" "FreeRTOS\Source\event_groups.obj" "FreeRTOS\Source\list.obj" "FreeRTOS\Source\queue.obj" "FreeRTOS\Source\tasks.obj" "FreeRTOS\Source\timers.obj" "FreeRTOS\Source\portable\CCS\ARM_CM4F\port.obj" "FreeRTOS\Source\portable\CCS\ARM_CM4F\portasm.obj" "FreeRTOS\Source\portable\MemMang\heap_4.obj" "HAL\LED.obj" "HAL\Temperature_sensor.obj" "HAL\pushbutton.obj" "MCAL\ADC.obj" "MCAL\GPIO.obj" "MCAL\GPTM.obj" "MCAL\NVIC.obj" "MCAL\UART0.obj" "MCAL\delay.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "APP\APP.d" "FreeRTOS\Source\event_groups.d" "FreeRTOS\Source\list.d" "FreeRTOS\Source\queue.d" "FreeRTOS\Source\tasks.d" "FreeRTOS\Source\timers.d" "FreeRTOS\Source\portable\CCS\ARM_CM4F\port.d" "FreeRTOS\Source\portable\MemMang\heap_4.d" "HAL\LED.d" "HAL\Temperature_sensor.d" "HAL\pushbutton.d" "MCAL\ADC.d" "MCAL\GPIO.d" "MCAL\GPTM.d" "MCAL\NVIC.d" "MCAL\UART0.d" "MCAL\delay.d" 
	-$(RM) "FreeRTOS\Source\portable\CCS\ARM_CM4F\portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

