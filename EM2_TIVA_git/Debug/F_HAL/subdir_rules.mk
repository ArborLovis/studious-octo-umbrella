################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F_HAL/%.obj: ../F_HAL/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/Ablage/FH-Joanneum/Semester_5/EM2/Git/studious-octo-umbrella/EM2_TIVA_git" --include_path="D:/Ablage/FH-Joanneum/Semester_5/EM2/Git/studious-octo-umbrella/EM2_TIVA_git/F_AL" --include_path="D:/Ablage/FH-Joanneum/Semester_5/EM2/Git/studious-octo-umbrella/EM2_TIVA_git/F_DL" --include_path="D:/Ablage/FH-Joanneum/Semester_5/EM2/Git/studious-octo-umbrella/EM2_TIVA_git/F_HAL" --include_path="D:/Tiva/TivaWare" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="F_HAL/$(basename $(<F)).d_raw" --obj_directory="F_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


