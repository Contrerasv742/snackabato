#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include "Protocol2.h"
#include "RCServo.h"
#include "MessageIDs.h"

//#define RC_SERVO_MIN_PULSE 600
//#define RC_SERVO_CENTER_PULSE 1500
//#define RC_SERVO_MAX_PULSE 2400

static int pulseWidth = 1000; // Start at center position

void aNOP_delay_1ms(int a) {
    for(int i=0; i<a; i++) {
        for (int j=0; i<80000; i++) {
            asm("nop");
        }
    }
}

/**
 * @Function RCServo_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware required and set it to the CENTER PULSE */
int RCServo_Init(void) {
    //PBCLK = 40MHz    = 0.000025 ms per tick
    //TMR3 = 40 MHz/32 = 1.25 MHz = 0.8 us per tick

    // 20 Hz = 50 ms period = 50,000 us
    // 50,000 us / 0.8 us = 62,500 ticks

    // Timer 3***************
    TMR3 = 0; // clear TMR3
    T3CON = 0; // clear timer 3 control register

    T3CONbits.TCKPS=5; // TMR3 prescaler 1:32 (3'b101)
    PR3 = 62500 - 1;  // TMR3 Period register value for 50 ms rollover (20 Hz)
    IFS0bits.T3IF = 0; // clear TMR3 interrupt flag status
    IPC3bits.T3IP = 3; // set TMR3 priority
    T3CONbits.ON = 1; // turn on TMR3

    // Output Compare 3 **********************
    TRISDbits.TRISD2 = 0; // Set RD2 (OC3) pin 6 as an output (OC3)

    OC3CON = 0; // clear OC3 control register
    OC3CONbits.OC32 = 0; // 16-bit mode
    OC3CONbits.OCTSEL = 1; // Timer3 is the clock source for this OCMP module
    OC3CONbits.OCM = 0b101; // Initialize OCx pin low; generate continuous output pulses on OCx pin
    OC3R = 0; // init primary compare register
    OC3RS = 600; // init secondary compare register to min value
    OC3CONbits.ON = 1; // turn on Output Compare Peripheral On bit

    IFS0bits.OC3IF = 0; // clear OC3 interrupt flag status
    IPC3bits.OC3IP = 3; // set OC3 priority
    IPC3bits.OC3IS = 1; // set OC3 sub-priority
    IEC0bits.OC3IE = 1; // enable OC3 interrupt

}

/**
 * @Function int RCServo_SetPulse(unsigned int inPulse)
 * @param inPulse, integer representing number of microseconds
 * @return SUCCESS or ERROR
 * @brief takes in microsecond count, converts to ticks and updates the internal variables
 * @warning This will update the timing for the next pulse, not the current one */
int RCServo_SetPulse(unsigned int inPulse) {
    // Clip the pulse width to between the minimum and maximum limits
    if (inPulse < 600) {
        inPulse = 600;
    } else if (inPulse > 2400) {
        inPulse = 2400;
    }
    pulseWidth = inPulse; // set pulse width
    return 1;
}

/**
 * @Function int RCServo_GetPulse(void)
 * @param None
 * @return Pulse in microseconds currently set */
unsigned int RCServo_GetPulse(void) {
    return pulseWidth;
}

/**
 * @Function int RCServo_GetRawTicks(void)
 * @param None
 * @return raw timer ticks required to generate current pulse. */
unsigned int RCServo_GetRawTicks(void) {
    return pulseWidth;
}

// Interrupt Service Routine for Output Compare 3
void __ISR(_OUTPUT_COMPARE_3_VECTOR) __OC3Interrupt(void) {
    
    OC3RS = pulseWidth / 0.8;  // Convert to timer ticks,Update Output Compare register

    IFS0bits.OC3IF = 0; // Clear interrupt flag
}

//#define RCSERVO_TEST
#ifdef RCSERVO_TEST

int main(int argc, char** argv) {
    //BOARD_Init();
    Protocol_Init(115200);
    RCServo_Init();
    //TRISE = 0x00;
    //PORTE = 0x00;
    
    char messageComp[100];
    sprintf(messageComp, "[DEBUG] RC Servo test harness compiled at %s %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(messageComp);
    
    while(1) {


        Packet_t currentPacket; // init packet struct to store incoming packet
 
        char payload[MAXPAYLOADLENGTH]; // init payload array
        uint8_t type, len;               // init type and length variables
 
        if (BuildRxPacket(&currentPacket, 0)) { // if incoming packet is built
            if (currentPacket.ID == ID_COMMAND_SERVO_PULSE) { // if incoming packet is servo
                
                // extract        payload 
                // ex: 0XCC 05 88 00 00 09 60 B96D0D0A

                // char messageComp1[100];
                // sprintf(messageComp1, "Payload  %02x %02x ", currentPacket.payLoad[3], currentPacket.payLoad[4]);
                // Protocol_SendDebugMessage(messageComp1);

                // scale pulse in ISR
                // set OC3 to drive the servo to the mapped location
                int newPulseWidth = ((currentPacket.payLoad[3] << 8) | (currentPacket.payLoad[4]));


                // char messageComp[100];
                // sprintf(messageComp, "newPulseWidth: %d \n", newPulseWidth);
                // Protocol_SendDebugMessage(messageComp);

                
                RCServo_SetPulse(newPulseWidth);

                // send response
                unsigned char byteArray[4];

                // Store in big-endian format
                byteArray[0] = (newPulseWidth >> 24) & 0xFF;  // Most significant byte
                byteArray[1] = (newPulseWidth >> 16) & 0xFF;
                byteArray[2] = (newPulseWidth >> 8)  & 0xFF;
                byteArray[3] = newPulseWidth & 0xFF;          // Least significant byte

                // Send response
                Protocol_SendPacket(5, ID_SERVO_RESPONSE, byteArray);
                

            }
        }
    }
    return 0;
}

#endif


