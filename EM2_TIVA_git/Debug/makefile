################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./F_AL/Scramble_data.obj" \
"./F_AL/radix2_fft.obj" \
"./F_DL/dl_LCD.obj" \
"./F_DL/dl_RF_Module.obj" \
"./F_DL/dl_general.obj" \
"./F_DL/dl_us.obj" \
"./F_HAL/hal_adc.obj" \
"./F_HAL/hal_gpio.obj" \
"./F_HAL/hal_init.obj" \
"./F_HAL/hal_pwm.obj" \
"./F_HAL/hal_ssi1.obj" \
"./F_HAL/hal_ssi2.obj" \
"./F_HAL/hal_timer2.obj" \
"./F_HAL/hal_uart1.obj" \
"./F_HAL/hal_us.obj" \
"./F_HAL/hal_usc.obj" \
"D:/Tiva/TivaWare/driverlib/ccs/Debug/driverlib.lib" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include F_AL/subdir_vars.mk
-include F_DL/subdir_vars.mk
-include F_HAL/subdir_vars.mk
-include subdir_rules.mk
-include F_AL/subdir_rules.mk
-include F_DL/subdir_rules.mk
-include F_HAL/subdir_rules.mk
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
EM2_TIVA.out \

EXE_OUTPUTS__QUOTED += \
"EM2_TIVA.out" \

BIN_OUTPUTS += \
EM2_TIVA.hex \

BIN_OUTPUTS__QUOTED += \
"EM2_TIVA.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "EM2_TIVA.out"

# Tool invocations
EM2_TIVA.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"EM2_TIVA.map" --heap_size=0 --stack_size=512 -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="EM2_TIVA_linkInfo.xml" --rom_model -o "EM2_TIVA.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

EM2_TIVA.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armhex"  -o "EM2_TIVA.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "F_AL\Scramble_data.obj" "F_AL\radix2_fft.obj" "F_DL\dl_LCD.obj" "F_DL\dl_RF_Module.obj" "F_DL\dl_general.obj" "F_DL\dl_us.obj" "F_HAL\hal_adc.obj" "F_HAL\hal_gpio.obj" "F_HAL\hal_init.obj" "F_HAL\hal_pwm.obj" "F_HAL\hal_ssi1.obj" "F_HAL\hal_ssi2.obj" "F_HAL\hal_timer2.obj" "F_HAL\hal_uart1.obj" "F_HAL\hal_us.obj" "F_HAL\hal_usc.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "F_AL\Scramble_data.d" "F_AL\radix2_fft.d" "F_DL\dl_LCD.d" "F_DL\dl_RF_Module.d" "F_DL\dl_general.d" "F_DL\dl_us.d" "F_HAL\hal_adc.d" "F_HAL\hal_gpio.d" "F_HAL\hal_init.d" "F_HAL\hal_pwm.d" "F_HAL\hal_ssi1.d" "F_HAL\hal_ssi2.d" "F_HAL\hal_timer2.d" "F_HAL\hal_uart1.d" "F_HAL\hal_us.d" "F_HAL\hal_usc.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

