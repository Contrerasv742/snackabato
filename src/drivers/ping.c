#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <ping.h>

#define TRIGGER LATDbits.LATD9//LATDbits.LATD9
#define TRIGGER_STATE 0
#define WAIT_STATE 1

static int pingPeriod = 0;
static int prev = 0;

void bNOP_delay_1ms(int a) {
    for(int i=0; i<a; i++) {
        for (int j=0; i<80000; i++) {
            asm("nop");
        }
    }
}

void bNOP_delay_1us(int a) {
    for(int i=0; i<a; i++) {
        for (int j=0; i<80; i++) {
            asm("nop");
        }
    }
}

volatile unsigned short risingEdge = 0;
volatile unsigned short fallingEdge = 0;
/**
 * @Function PingSensor_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for PingSensor with the needed interrupts */
int Ping_Init(void) {
    TRISDbits.TRISD9 = 0;//TRISDbits.TRISD9 = 0; // Set RD9 (TRIGGER) pin 7 as an output (Y-8)
    
    // Configure Timer 2 *******************************
    //(as much resolution as possible consistent with > 11.68msec rollover.
    // TMR2 rollover to be 

    // PBCLK = 40MHz = 0.000025 ms per tick
    // TMR2 = 40 MHz/ 8 = 5 MHz = 0.2 us per tick
    // PR2 = 58400 (11.68 ms / 0.2 us = 58400)

    TMR2 = 0; // clear TMR2
    T2CON = 0; // clear timer 2 control register

    T2CONbits.TCKPS = 3; // TMR2 prescaler 1:8 (3'b011)
    PR2 = 60000; // TMR2 Period register value for >11.68 ms rollover
    
    //IFS0bits.T2IF = 0; // clear TMR2 interrupt flag status
    //IPC2bits.T2IP = 3; // set TMR2 priority

    T2CONbits.ON = 1; // turn on TMR2


    // configure Input Capture 3 *******************************
    TRISDbits.TRISD10 = 1;//TRISDbits.TRISD10 = 1; // Set RD10 (IC3) pin 8 as an input
    
    IC3CON = 0; // clear Input Capture 3 control register
    int rData = IC3BUF; // clear the IC3 buffer
    IC3CONbits.ICTMR = 1; // use Timer 2 for capture source
    IC3CONbits.ICM = 0b001; //  Edge Detect mode ? every edge (rising and falling)
    IC3CONbits.ON = 1; // turn on IC3

    IFS0bits.IC3IF = 0; // clear IC3 interrupt flag status
    IEC0bits.IC3IE = 1; // enable IC3 interrupts
    IPC3bits.IC3IP = 3; // set IC3 priority


    // configure timer 4 *******************************
    // TMR4 rollover to be 60 ms (60000 us) 

    // PBCLK = 40MHz = 0.000025 ms per tick
    // TMR4 = 40 MHz/256 = 156.25 kHz = 6.4 us per tick
    // PR4 = 9375  (60000 us / 6.4 us = 9375)
    /*
    TMR5 = 0; // clear TMR4
    T5CON = 0; // clear timer 4 control register

    T5CONbits.TCKPS = 0b111; // TMR4 prescaler 1:256 (3'b111)
    PR5 = 9375-1; // TMR4 Period register value for 60 ms rollover
    
    IFS0bits.T5IF = 0; // clear TMR4 interrupt flag status
    IEC0bits.T5IE = 1; // enable TMR4 interrupts
    IPC5bits.T5IP = 3; // set TMR4 priority

    T5CONbits.ON = 1; // turn on TMR4
     * */
    TMR5 = 0; // clear TMR4
    T5CON = 0; // clear timer 4 control register

    T5CONbits.TCKPS = 0b110; // TMR4 prescaler 1:4 (3'b010)
    PR5 = 37493; // TMR4 Period register value for 60 ms rollover
    
    IFS0bits.T5IF = 0; // clear TMR4 interrupt flag status
    IEC0bits.T5IE = 1; // enable TMR4 interrupts
    IPC5bits.T5IP = 3; // set TMR4 priority

    T5CONbits.ON = 1; // turn on TMR4
}


/**
 * @Function int PingSensor_GetDistance(void)
 * @param None
 * @return Unsigned Short corresponding to distance in millimeters */
unsigned short Ping_GetDistance(void) {
    // Base Case: Ping Period out of bounds
    if ((pingPeriod == 0) || 
        (pingPeriod > 23200)) {
        //Ping_Init();
        return 0xFFFF;
    }
    
    unsigned short dist = pingPeriod / 58;
    
    if (dist < 400){
        prev = dist;
        return dist;
    }
    
    //Ping_Init();
    return dist; // return ping period in cm?
}


void __ISR(_TIMER_5_VECTOR) Timer5IntHandler(void) {
    /*
    TRIGGER = 1; // Set Trigger pin HIGH
    bNOP_delay_1us(10); // Delay (~10?s)
    TRIGGER = 0; // Set Trigger pin LOW
    
    IFS0bits.T5IF = 0; // clear interrupt flag
    */
    
    static int state = TRIGGER_STATE;
        // state machine of your design
        switch (state){
            case TRIGGER_STATE: //trigger state
                TRIGGER = 1; //write pin to high
                PR5 = 7; //time next interrupt for 10 microseconds
                state = WAIT_STATE; //change states
                break;

            case WAIT_STATE: //waiting state
                TRIGGER = 0; //write pin to low
                PR5 = 37493; //time next interrupt for 60 milliseconds
                state = TRIGGER_STATE; //change states
                break;
        }
    IFS0bits.T5IF = 0;
}


void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL3SOFT) __IC3Interrupt(void) {
    unsigned short timestamp = (IC3BUF & 0xFFFF); // Read 16-bit IC3BUF
    //printf("here\r\n");
    /*
    if (PORTDbits.RD10) { // If input pin is HIGH, it's a rising edge (Y-6))
        risingEdge = timestamp;
    } else { // Falling edge
        fallingEdge = timestamp;
        pingPeriod = (fallingEdge - risingEdge); // Calculate time-of-flight
    }*/
    if (PORTDbits.RD10) { // Rising edge
        risingEdge = timestamp;
    } else { // Falling edge
        fallingEdge = timestamp;
        
        // Handle timer overflow
        if (fallingEdge >= risingEdge) {
            pingPeriod = (fallingEdge - risingEdge);
        } else {
            // Timer overflowed between edges
            pingPeriod = (65536 - risingEdge) + fallingEdge;
        }
    }
    
    IFS0bits.IC3IF = 0; // Clear interrupt flag
}



//#define PINGSENSOR_TEST
#ifdef PINGSENSOR_TEST

int main(int argc, char** argv) {
    //BOARD_Init();
    Protocol_Init(115200);
    PingSensor_Init();
    TRISE = 0x00;
    PORTE = 0x00;
    
    char messageComp[100];
    sprintf(messageComp, "[DEBUG] Ping Sensor test harness compiled at %s %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(messageComp);
    
    while(1) {
        unsigned short distance = PingSensor_GetDistance();
        //sprintf(messageComp, "[DEBUG] Distance: %x \n", distance);
        //Protocol_SendDebugMessage(messageComp);

        // send response
        unsigned char byteArray[2];

        // Store in big-endian format
        byteArray[0] = (distance >> 8)  & 0xFF;
        byteArray[1] = distance & 0xFF;          // Least significant byte

        Protocol_SendPacket(3, ID_PING_DISTANCE, byteArray); // Send only 2 bytes

        bNOP_delay_1ms(100);
    }
    return 0;
}

#endif