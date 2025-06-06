#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Snackoboto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Snackoboto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/app/main.c ../src/drivers/AD.c ../src/drivers/BOARD.c ../src/drivers/HallSensor.c ../src/drivers/IO_Ports.c ../src/drivers/IR_Sensor.c ../src/drivers/LED.c ../src/drivers/ping.c ../src/drivers/pwm.c ../src/drivers/RC_Servo.c ../src/drivers/TapeSensor.c ../src/drivers/Snackoboto.c ../../../Downloads/ece118_files/ece118_base/serial.c ../src/drivers/TwoStepper.c ../src/events/HallEventChecker.c ../src/events/IRPeakEventChecker.c ../src/events/TapeEventChecker.c ../src/events/ObstacleEventChecker.c ../src/framework/ES_CheckEvents.c ../src/framework/ES_Framework.c ../src/framework/ES_KeyboardInput.c ../src/framework/ES_LookupTables.c ../src/framework/ES_PostList.c ../src/framework/ES_Queue.c ../src/framework/ES_TattleTale.c ../src/framework/ES_Timers.c ../src/framework/ES_TimerService.c ../src/state_machine/ObstacleSubHSM.c ../src/state_machine/SearchingSubHSM.c ../src/state_machine/SnackobotoHSM.c ../src/state_machine/TargetLAimSubHSM.c ../src/state_machine/TargetLSubHSM.c ../src/state_machine/TargetRAimSubHSM.c ../src/state_machine/TargetRSubHSM.c ../src/events/KnockdownService.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/659850791/main.o ${OBJECTDIR}/_ext/1639450193/AD.o ${OBJECTDIR}/_ext/1639450193/BOARD.o ${OBJECTDIR}/_ext/1639450193/HallSensor.o ${OBJECTDIR}/_ext/1639450193/IO_Ports.o ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o ${OBJECTDIR}/_ext/1639450193/LED.o ${OBJECTDIR}/_ext/1639450193/ping.o ${OBJECTDIR}/_ext/1639450193/pwm.o ${OBJECTDIR}/_ext/1639450193/RC_Servo.o ${OBJECTDIR}/_ext/1639450193/TapeSensor.o ${OBJECTDIR}/_ext/1639450193/Snackoboto.o ${OBJECTDIR}/_ext/2035180596/serial.o ${OBJECTDIR}/_ext/1639450193/TwoStepper.o ${OBJECTDIR}/_ext/330559661/HallEventChecker.o ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o ${OBJECTDIR}/_ext/1171087748/ES_Framework.o ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o ${OBJECTDIR}/_ext/1171087748/ES_PostList.o ${OBJECTDIR}/_ext/1171087748/ES_Queue.o ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o ${OBJECTDIR}/_ext/1171087748/ES_Timers.o ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o ${OBJECTDIR}/_ext/330559661/KnockdownService.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/659850791/main.o.d ${OBJECTDIR}/_ext/1639450193/AD.o.d ${OBJECTDIR}/_ext/1639450193/BOARD.o.d ${OBJECTDIR}/_ext/1639450193/HallSensor.o.d ${OBJECTDIR}/_ext/1639450193/IO_Ports.o.d ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o.d ${OBJECTDIR}/_ext/1639450193/LED.o.d ${OBJECTDIR}/_ext/1639450193/ping.o.d ${OBJECTDIR}/_ext/1639450193/pwm.o.d ${OBJECTDIR}/_ext/1639450193/RC_Servo.o.d ${OBJECTDIR}/_ext/1639450193/TapeSensor.o.d ${OBJECTDIR}/_ext/1639450193/Snackoboto.o.d ${OBJECTDIR}/_ext/2035180596/serial.o.d ${OBJECTDIR}/_ext/1639450193/TwoStepper.o.d ${OBJECTDIR}/_ext/330559661/HallEventChecker.o.d ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o.d ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o.d ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o.d ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1171087748/ES_Framework.o.d ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o.d ${OBJECTDIR}/_ext/1171087748/ES_PostList.o.d ${OBJECTDIR}/_ext/1171087748/ES_Queue.o.d ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1171087748/ES_Timers.o.d ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o.d ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o.d ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o.d ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o.d ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o.d ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o.d ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o.d ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o.d ${OBJECTDIR}/_ext/330559661/KnockdownService.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/659850791/main.o ${OBJECTDIR}/_ext/1639450193/AD.o ${OBJECTDIR}/_ext/1639450193/BOARD.o ${OBJECTDIR}/_ext/1639450193/HallSensor.o ${OBJECTDIR}/_ext/1639450193/IO_Ports.o ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o ${OBJECTDIR}/_ext/1639450193/LED.o ${OBJECTDIR}/_ext/1639450193/ping.o ${OBJECTDIR}/_ext/1639450193/pwm.o ${OBJECTDIR}/_ext/1639450193/RC_Servo.o ${OBJECTDIR}/_ext/1639450193/TapeSensor.o ${OBJECTDIR}/_ext/1639450193/Snackoboto.o ${OBJECTDIR}/_ext/2035180596/serial.o ${OBJECTDIR}/_ext/1639450193/TwoStepper.o ${OBJECTDIR}/_ext/330559661/HallEventChecker.o ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o ${OBJECTDIR}/_ext/1171087748/ES_Framework.o ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o ${OBJECTDIR}/_ext/1171087748/ES_PostList.o ${OBJECTDIR}/_ext/1171087748/ES_Queue.o ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o ${OBJECTDIR}/_ext/1171087748/ES_Timers.o ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o ${OBJECTDIR}/_ext/330559661/KnockdownService.o

# Source Files
SOURCEFILES=../src/app/main.c ../src/drivers/AD.c ../src/drivers/BOARD.c ../src/drivers/HallSensor.c ../src/drivers/IO_Ports.c ../src/drivers/IR_Sensor.c ../src/drivers/LED.c ../src/drivers/ping.c ../src/drivers/pwm.c ../src/drivers/RC_Servo.c ../src/drivers/TapeSensor.c ../src/drivers/Snackoboto.c ../../../Downloads/ece118_files/ece118_base/serial.c ../src/drivers/TwoStepper.c ../src/events/HallEventChecker.c ../src/events/IRPeakEventChecker.c ../src/events/TapeEventChecker.c ../src/events/ObstacleEventChecker.c ../src/framework/ES_CheckEvents.c ../src/framework/ES_Framework.c ../src/framework/ES_KeyboardInput.c ../src/framework/ES_LookupTables.c ../src/framework/ES_PostList.c ../src/framework/ES_Queue.c ../src/framework/ES_TattleTale.c ../src/framework/ES_Timers.c ../src/framework/ES_TimerService.c ../src/state_machine/ObstacleSubHSM.c ../src/state_machine/SearchingSubHSM.c ../src/state_machine/SnackobotoHSM.c ../src/state_machine/TargetLAimSubHSM.c ../src/state_machine/TargetLSubHSM.c ../src/state_machine/TargetRAimSubHSM.c ../src/state_machine/TargetRSubHSM.c ../src/events/KnockdownService.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Snackoboto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/659850791/main.o: ../src/app/main.c  .generated_files/flags/default/1e89523a1854b815e37d64e2db005495cbb9df53 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/659850791" 
	@${RM} ${OBJECTDIR}/_ext/659850791/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/659850791/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/659850791/main.o.d" -o ${OBJECTDIR}/_ext/659850791/main.o ../src/app/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/AD.o: ../src/drivers/AD.c  .generated_files/flags/default/8fba44ebeaac691be5c7682eb7db910038965f59 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/AD.o.d" -o ${OBJECTDIR}/_ext/1639450193/AD.o ../src/drivers/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/BOARD.o: ../src/drivers/BOARD.c  .generated_files/flags/default/4e04df0059ccb70f3928e92671f05f9485eb2702 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/BOARD.o.d" -o ${OBJECTDIR}/_ext/1639450193/BOARD.o ../src/drivers/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/HallSensor.o: ../src/drivers/HallSensor.c  .generated_files/flags/default/1d00afbd5eebfdc49a26c8dca289d3941d0b3014 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/HallSensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/HallSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/HallSensor.o.d" -o ${OBJECTDIR}/_ext/1639450193/HallSensor.o ../src/drivers/HallSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/IO_Ports.o: ../src/drivers/IO_Ports.c  .generated_files/flags/default/c60d8f277363592eb974655df2cb4bf698874ad1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1639450193/IO_Ports.o ../src/drivers/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/IR_Sensor.o: ../src/drivers/IR_Sensor.c  .generated_files/flags/default/41b9421f7cf88c6b91b401adc7b158d1dcbc8bf8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/IR_Sensor.o.d" -o ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o ../src/drivers/IR_Sensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/LED.o: ../src/drivers/LED.c  .generated_files/flags/default/a160fea6452bcaaf6ec84cdf838f05214761bd02 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/LED.o.d" -o ${OBJECTDIR}/_ext/1639450193/LED.o ../src/drivers/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/ping.o: ../src/drivers/ping.c  .generated_files/flags/default/81ddd34975fe3d04adadbfa7a7635ab99e9a32a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/ping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/ping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/ping.o.d" -o ${OBJECTDIR}/_ext/1639450193/ping.o ../src/drivers/ping.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/pwm.o: ../src/drivers/pwm.c  .generated_files/flags/default/7af5615fb62a2cc3be70dce073e6870a8716f665 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/pwm.o.d" -o ${OBJECTDIR}/_ext/1639450193/pwm.o ../src/drivers/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/RC_Servo.o: ../src/drivers/RC_Servo.c  .generated_files/flags/default/bcc682c70da289b773201d37c0c257f897646dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1639450193/RC_Servo.o ../src/drivers/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/TapeSensor.o: ../src/drivers/TapeSensor.c  .generated_files/flags/default/dc296b0d694c994f4fbe61cad7d9b02b0f9f5706 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/TapeSensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/TapeSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/TapeSensor.o.d" -o ${OBJECTDIR}/_ext/1639450193/TapeSensor.o ../src/drivers/TapeSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/Snackoboto.o: ../src/drivers/Snackoboto.c  .generated_files/flags/default/2eadb2234b8f1381c8bacfae22d3bca15202b6d3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/Snackoboto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/Snackoboto.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/Snackoboto.o.d" -o ${OBJECTDIR}/_ext/1639450193/Snackoboto.o ../src/drivers/Snackoboto.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2035180596/serial.o: ../../../Downloads/ece118_files/ece118_base/serial.c  .generated_files/flags/default/adb375c3cd28b7319879029c97c79c975960dd9b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2035180596" 
	@${RM} ${OBJECTDIR}/_ext/2035180596/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/2035180596/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/2035180596/serial.o.d" -o ${OBJECTDIR}/_ext/2035180596/serial.o ../../../Downloads/ece118_files/ece118_base/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/TwoStepper.o: ../src/drivers/TwoStepper.c  .generated_files/flags/default/8be52d61748ce858b06768a58595ccc4fe1fc677 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/TwoStepper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/TwoStepper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/TwoStepper.o.d" -o ${OBJECTDIR}/_ext/1639450193/TwoStepper.o ../src/drivers/TwoStepper.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/HallEventChecker.o: ../src/events/HallEventChecker.c  .generated_files/flags/default/33c50ad8c710737bc2661695f2b42c17b80d7cd5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/HallEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/HallEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/HallEventChecker.o.d" -o ${OBJECTDIR}/_ext/330559661/HallEventChecker.o ../src/events/HallEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o: ../src/events/IRPeakEventChecker.c  .generated_files/flags/default/302d8214a8af3b92fb036cf94e51d908d54ef20 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o.d" -o ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o ../src/events/IRPeakEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/TapeEventChecker.o: ../src/events/TapeEventChecker.c  .generated_files/flags/default/56615d66941a6c8f98ca1301fd55912b81bb36d8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/TapeEventChecker.o.d" -o ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o ../src/events/TapeEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o: ../src/events/ObstacleEventChecker.c  .generated_files/flags/default/70cd6c058f596e1725dbd4a0ae6ad1d3a9240ce5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o.d" -o ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o ../src/events/ObstacleEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o: ../src/framework/ES_CheckEvents.c  .generated_files/flags/default/f170e4b101309c45b78c5fcdeb72fa55982afc9d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o ../src/framework/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_Framework.o: ../src/framework/ES_Framework.c  .generated_files/flags/default/789552d43f357a94256852667fea8a9c786d8425 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_Framework.o ../src/framework/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o: ../src/framework/ES_KeyboardInput.c  .generated_files/flags/default/538c112759e1f3ff5e68ca62533d7bbf466d303f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o ../src/framework/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o: ../src/framework/ES_LookupTables.c  .generated_files/flags/default/f2869587ed417a06f176c5d66302d10366d07b89 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o ../src/framework/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_PostList.o: ../src/framework/ES_PostList.c  .generated_files/flags/default/1a3a71019a841b7e82cc825a6b3503812c57919 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_PostList.o ../src/framework/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_Queue.o: ../src/framework/ES_Queue.c  .generated_files/flags/default/c161907d8350066b8f75f3abcf6d41e4fae3391e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_Queue.o ../src/framework/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o: ../src/framework/ES_TattleTale.c  .generated_files/flags/default/6ec1d6dbb9f4490eed40b7aeacc3c4149df5aa8e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o ../src/framework/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_Timers.o: ../src/framework/ES_Timers.c  .generated_files/flags/default/897c948db02faf65658b5dd961ec999bc2cac167 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_Timers.o ../src/framework/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_TimerService.o: ../src/framework/ES_TimerService.c  .generated_files/flags/default/60c0994bd75a69872171740dbb433fed9c1b623b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_TimerService.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o ../src/framework/ES_TimerService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o: ../src/state_machine/ObstacleSubHSM.c  .generated_files/flags/default/64abb26633e24e9ca5fe4e3a9ed07e779e07835f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o ../src/state_machine/ObstacleSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o: ../src/state_machine/SearchingSubHSM.c  .generated_files/flags/default/8ff51e64d2f9057e75ae7bc76450233a56d53c7e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o ../src/state_machine/SearchingSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o: ../src/state_machine/SnackobotoHSM.c  .generated_files/flags/default/63bbeabd93210f6b53142444aeb9989e11986cbb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o ../src/state_machine/SnackobotoHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o: ../src/state_machine/TargetLAimSubHSM.c  .generated_files/flags/default/c9ffd7b6b9156c5c1241c555132c1e2c78beafca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o ../src/state_machine/TargetLAimSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o: ../src/state_machine/TargetLSubHSM.c  .generated_files/flags/default/91141f8b081a0ff40a7e6694d07e9d35f936baa5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o ../src/state_machine/TargetLSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o: ../src/state_machine/TargetRAimSubHSM.c  .generated_files/flags/default/850661e3b7c4b2d1ff5c399f6b3e2839084eb97a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o ../src/state_machine/TargetRAimSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o: ../src/state_machine/TargetRSubHSM.c  .generated_files/flags/default/94d53ce09a141f44e1296dd167f7e7d73ad04a76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o ../src/state_machine/TargetRSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/KnockdownService.o: ../src/events/KnockdownService.c  .generated_files/flags/default/157f63b02890425bdfd9c1cd4dc40f1346e1c27e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/KnockdownService.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/KnockdownService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/KnockdownService.o.d" -o ${OBJECTDIR}/_ext/330559661/KnockdownService.o ../src/events/KnockdownService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/659850791/main.o: ../src/app/main.c  .generated_files/flags/default/87f6dd0f58450f2b3c40b31554a20c5a5c9d372b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/659850791" 
	@${RM} ${OBJECTDIR}/_ext/659850791/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/659850791/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/659850791/main.o.d" -o ${OBJECTDIR}/_ext/659850791/main.o ../src/app/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/AD.o: ../src/drivers/AD.c  .generated_files/flags/default/410a9679147fe73296dccd8a600fe88691b1a0cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/AD.o.d" -o ${OBJECTDIR}/_ext/1639450193/AD.o ../src/drivers/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/BOARD.o: ../src/drivers/BOARD.c  .generated_files/flags/default/c44571a4623b449f9b57b808fe48c334e66d7b70 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/BOARD.o.d" -o ${OBJECTDIR}/_ext/1639450193/BOARD.o ../src/drivers/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/HallSensor.o: ../src/drivers/HallSensor.c  .generated_files/flags/default/f8be6c3ca95e4b42998836743d22d326d6d23b5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/HallSensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/HallSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/HallSensor.o.d" -o ${OBJECTDIR}/_ext/1639450193/HallSensor.o ../src/drivers/HallSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/IO_Ports.o: ../src/drivers/IO_Ports.c  .generated_files/flags/default/985eeec3ea7646ec3eab21f3ac07ec42139d1719 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1639450193/IO_Ports.o ../src/drivers/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/IR_Sensor.o: ../src/drivers/IR_Sensor.c  .generated_files/flags/default/3a2347ea6caa1d599eaa6c6e6c36e5920b3e4c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/IR_Sensor.o.d" -o ${OBJECTDIR}/_ext/1639450193/IR_Sensor.o ../src/drivers/IR_Sensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/LED.o: ../src/drivers/LED.c  .generated_files/flags/default/e2a8f3e7b88b7f54184d5cd26630482580ed2fdc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/LED.o.d" -o ${OBJECTDIR}/_ext/1639450193/LED.o ../src/drivers/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/ping.o: ../src/drivers/ping.c  .generated_files/flags/default/e414e977406a9cddf155e8d52fa6dd50c7d6dc67 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/ping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/ping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/ping.o.d" -o ${OBJECTDIR}/_ext/1639450193/ping.o ../src/drivers/ping.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/pwm.o: ../src/drivers/pwm.c  .generated_files/flags/default/41dad7d5361b71e7af12ded56009d50d2ecc7eb1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/pwm.o.d" -o ${OBJECTDIR}/_ext/1639450193/pwm.o ../src/drivers/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/RC_Servo.o: ../src/drivers/RC_Servo.c  .generated_files/flags/default/a4bcc5af581a1d42aadb0bf36f00d85a30cd949f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1639450193/RC_Servo.o ../src/drivers/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/TapeSensor.o: ../src/drivers/TapeSensor.c  .generated_files/flags/default/37074d078876d5205bd4bd3b315cecfd266955c5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/TapeSensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/TapeSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/TapeSensor.o.d" -o ${OBJECTDIR}/_ext/1639450193/TapeSensor.o ../src/drivers/TapeSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/Snackoboto.o: ../src/drivers/Snackoboto.c  .generated_files/flags/default/f1a7934fe44944724b3d52acdaa451832064e890 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/Snackoboto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/Snackoboto.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/Snackoboto.o.d" -o ${OBJECTDIR}/_ext/1639450193/Snackoboto.o ../src/drivers/Snackoboto.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2035180596/serial.o: ../../../Downloads/ece118_files/ece118_base/serial.c  .generated_files/flags/default/879d78215fe793a896ac5441857aac29549915ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2035180596" 
	@${RM} ${OBJECTDIR}/_ext/2035180596/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/2035180596/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/2035180596/serial.o.d" -o ${OBJECTDIR}/_ext/2035180596/serial.o ../../../Downloads/ece118_files/ece118_base/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1639450193/TwoStepper.o: ../src/drivers/TwoStepper.c  .generated_files/flags/default/9626fa09a7302832d75c0ecb112e60cc92f78461 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1639450193" 
	@${RM} ${OBJECTDIR}/_ext/1639450193/TwoStepper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1639450193/TwoStepper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1639450193/TwoStepper.o.d" -o ${OBJECTDIR}/_ext/1639450193/TwoStepper.o ../src/drivers/TwoStepper.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/HallEventChecker.o: ../src/events/HallEventChecker.c  .generated_files/flags/default/59dad2533c70339df49f347855633a8d8ab43656 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/HallEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/HallEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/HallEventChecker.o.d" -o ${OBJECTDIR}/_ext/330559661/HallEventChecker.o ../src/events/HallEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o: ../src/events/IRPeakEventChecker.c  .generated_files/flags/default/b65a6d52b6191f161aa419e4923494bbe096975 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o.d" -o ${OBJECTDIR}/_ext/330559661/IRPeakEventChecker.o ../src/events/IRPeakEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/TapeEventChecker.o: ../src/events/TapeEventChecker.c  .generated_files/flags/default/bbcf840233e17146e042e18a7361a414e876ed2d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/TapeEventChecker.o.d" -o ${OBJECTDIR}/_ext/330559661/TapeEventChecker.o ../src/events/TapeEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o: ../src/events/ObstacleEventChecker.c  .generated_files/flags/default/a8a1d7e65b10f9f15a507071384bccbf98df336d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o.d" -o ${OBJECTDIR}/_ext/330559661/ObstacleEventChecker.o ../src/events/ObstacleEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o: ../src/framework/ES_CheckEvents.c  .generated_files/flags/default/51040c200bd5dc948b668eefce514c98416d62b4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_CheckEvents.o ../src/framework/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_Framework.o: ../src/framework/ES_Framework.c  .generated_files/flags/default/ad07d2876aeec6e3149f404c502896612075c42c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_Framework.o ../src/framework/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o: ../src/framework/ES_KeyboardInput.c  .generated_files/flags/default/539f9ff7ec6e0a7ff90e91a0c418d76a6579475e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_KeyboardInput.o ../src/framework/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o: ../src/framework/ES_LookupTables.c  .generated_files/flags/default/b02819fc5bbdaa63364478e6448302ec0131b8bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_LookupTables.o ../src/framework/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_PostList.o: ../src/framework/ES_PostList.c  .generated_files/flags/default/ad30334f905676ad21bbde806faf13bee5298d83 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_PostList.o ../src/framework/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_Queue.o: ../src/framework/ES_Queue.c  .generated_files/flags/default/125036e5a1b664579b8c862fb01baa6446569dc5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_Queue.o ../src/framework/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o: ../src/framework/ES_TattleTale.c  .generated_files/flags/default/90b5f73393f2225d7a466dabc7beca1ecc29e887 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_TattleTale.o ../src/framework/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_Timers.o: ../src/framework/ES_Timers.c  .generated_files/flags/default/55a0826b62a85c16185a5b7103036fe691d01c1d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_Timers.o ../src/framework/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171087748/ES_TimerService.o: ../src/framework/ES_TimerService.c  .generated_files/flags/default/5ba89df94e6828c45c0189aa5c9218456274b25 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171087748" 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1171087748/ES_TimerService.o.d" -o ${OBJECTDIR}/_ext/1171087748/ES_TimerService.o ../src/framework/ES_TimerService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o: ../src/state_machine/ObstacleSubHSM.c  .generated_files/flags/default/1eb7c9f9a83ccc29d60b34eaa081b8e7ee0b4ece .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/ObstacleSubHSM.o ../src/state_machine/ObstacleSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o: ../src/state_machine/SearchingSubHSM.c  .generated_files/flags/default/6ed6ed1ecfea6d6e26447a1b9bdb4ece727ba484 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/SearchingSubHSM.o ../src/state_machine/SearchingSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o: ../src/state_machine/SnackobotoHSM.c  .generated_files/flags/default/974bd915556af1ad8528165cafaede9aa75b17d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/SnackobotoHSM.o ../src/state_machine/SnackobotoHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o: ../src/state_machine/TargetLAimSubHSM.c  .generated_files/flags/default/78521501e294cc9810f7f39d3f4cf4f7f9341f31 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/TargetLAimSubHSM.o ../src/state_machine/TargetLAimSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o: ../src/state_machine/TargetLSubHSM.c  .generated_files/flags/default/676751464c0098f18a99bff5cab27ebf7cc6bc8e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/TargetLSubHSM.o ../src/state_machine/TargetLSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o: ../src/state_machine/TargetRAimSubHSM.c  .generated_files/flags/default/319e2b20b55c4852868f624dd5b279265b10449e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/TargetRAimSubHSM.o ../src/state_machine/TargetRAimSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o: ../src/state_machine/TargetRSubHSM.c  .generated_files/flags/default/ce1f29881b6dc9fc56efdb99dee5d1eaad231523 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1956984033" 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o.d" -o ${OBJECTDIR}/_ext/1956984033/TargetRSubHSM.o ../src/state_machine/TargetRSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/330559661/KnockdownService.o: ../src/events/KnockdownService.c  .generated_files/flags/default/3970c2bb33077cde9bc39cc320e60670c5ac3308 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/330559661" 
	@${RM} ${OBJECTDIR}/_ext/330559661/KnockdownService.o.d 
	@${RM} ${OBJECTDIR}/_ext/330559661/KnockdownService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../../../Downloads/ece118_files/ece118_base" -I"../include/drivers" -I"../include/events" -I"../include/framework" -I"../include/state_machine" -I"../src/app" -I"../src/drivers" -I"../src/events" -I"../src/framework" -I"../src/motor" -I"../src/state_machine" -MP -MMD -MF "${OBJECTDIR}/_ext/330559661/KnockdownService.o.d" -o ${OBJECTDIR}/_ext/330559661/KnockdownService.o ../src/events/KnockdownService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Snackoboto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Snackoboto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=128,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Snackoboto.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Snackoboto.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=128,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Snackoboto.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
