
#include <xc.h>
#include <sys/attribs.h>
#include "uart.h"
#include "BOARD.h"
#include "stdio.h"
#include "MessageIDs.h"
#include "Protocol2.h"

#define PBCLK 40000000UL // System clock frequency (40 MHz)
#define BAUD 115200

#define BTN1 PORTFbits.RF1 // for debug

// Define rxBuffer and txBuffer
circularBuffer rxBuffer;
circularBuffer txBuffer;

// delay for 10ms
void NOP_delay_10ms(void) {
    for (int i=0; i<800000; i++) {
        asm("nop");
    }
}
 
/**
 * @Function Uart_Init(unsigned long baudrate)
 * @param baudrate
 * @return none
 * @brief  Initializes UART1 to baudrate N81 and creates circ buffers
 * @author instructor ece121 W2022 */
void Uart_Init(unsigned long baudRate) {
    U1MODE = 0x0; // Clear UART mode register
    U1STA = 0x0;  // Clear UART status register

    U1BRG = ((PBCLK / (baudRate * 16)) - 1); // Baud rate generator calculation

    U1MODEbits.PDSEL = 0; // 8 data bits no parity
    U1MODEbits.STSEL = 0; // 1 stop bit
    
    U1MODEbits.ON = 1;    // Turn on UART
    U1STAbits.URXEN = 1; // Turn on receiver
    U1STAbits.UTXEN = 1; // Turn on transmitter

    // Enable Transmit Interrupt Enable Control bit
    IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 1;

    // Interrupt mode select
    U1STAbits.UTXISEL = 1; // Interrupt is generated and asserted when all characters have been transmitted
    U1STAbits.URXISEL = 0; // Interrupt flag is set when a character is received

    // Clear Interrupt Flag Status bit 
    IFS0bits.U1TXIF = 0;
    IFS0bits.U1RXIF = 0;

    // set priority and sub-priority
    IPC6bits.U1IP = 3;
    IPC6bits.U1IS = 1;

    // Enable multi-vector mode --not sure about this
    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();

    // Initialize buffers
    rxBuffer.head = 0;
    rxBuffer.tail = 0;
    txBuffer.head = 0;
    txBuffer.tail = 0;
}

//  circular buffer enqueue  function
int enqueue(circularBuffer *cb, char data) {
    unsigned int nextTail = (cb->tail + 1) % BUFFER_SIZE;
    if (nextTail == cb->head) {
        return 0; // Full Buffer
    }
    cb->buffer[cb->tail] = data;
    cb->tail = nextTail;
    IFS0bits.U1TXIF = 1; // tx interrupt flag
    return 1; // Success
}

//  circular buffer dequeue  function
int dequeue(circularBuffer *cb, char *data) {
    if (cb->head == cb->tail) {
        return 0; // Buffer empty, nothing to read
    }
    *data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    return 1; // Success
}

// UART1 interrupt handler
void __ISR(_UART1_VECTOR, IPL3AUTO) IntUart1Handler(void) {
    // Handle received data
    if (IFS0bits.U1RXIF) {
        while (U1STAbits.URXDA) { // While data is available in receive buffer
            char receivedChar = U1RXREG; // Read received character
            enqueue(&rxBuffer, receivedChar); // Store in RX buffer
        }
        IFS0bits.U1RXIF = 0; // Clear receive interrupt flag
    }
    // Handle transmit data
    if (IFS0bits.U1TXIF) {
        char data;
        while (!U1STAbits.UTXBF) {
            if (dequeue(&txBuffer, &data)) {
                U1TXREG = data; // Send character
            } else {
                IEC0bits.U1TXIE = 0; // Disable TX interrupt if no data to send
                break;
            }
        }
        IFS0bits.U1TXIF = 0; // Clear transmit interrupt flag
    }
}
 
/**
 * @Function int PutChar(char ch)
 * @param ch - the character to be sent out the serial port
 * @return True if successful, else False if the buffer is full or busy.
 * @brief  adds char to the end of the TX circular buffer
 * @author instrutor ECE121 W2022 */
int PutChar(char ch) {
    if (!enqueue(&txBuffer, ch)) {  
        return 0;  //buffer is full, can't add character
    }

    //enable TX interrupt to start sending
    IEC0bits.U1TXIE = 1;
    IFS0bits.U1TXIF = 1;
    return 1;  //success
}
 
/**
 * @Function unsigned char GetChar(void)
 * @param None.
 * @return NULL for error or a Char in the argument.
 * @brief  dequeues a character from the RX buffer,
 * @author instructor, ECE121 W2022 */
unsigned char GetChar(unsigned char *ch) {
    if (!dequeue(&rxBuffer, ch)) {
        return 0; // Buffer empty, nothing to read
    }
    return 1; // Success
}

 
//#define PART3
#ifdef PART3
int main(int argc, char** argv) {
    BOARD_Init();
    Protocol_Init(115200);
    TRISE = 0x00;
    PORTE = 0x00;
    

    char messageComp[100];
    sprintf(messageComp, "[DEBUG] Application Program layer compiled at %s %s\n", __DATE__, __TIME__);
    Protocol_SendDebugMessage(messageComp);

    while(1) {
       Packet_t currentPacket; // init packet struct to store incoming packet

       char payload[MAXPAYLOADLENGTH]; // init payload array
       uint8_t type, len;               // init type and length variables

        if (BuildRxPacket(&currentPacket, 0)) { // if incoming packet is built
            if (currentPacket.ID == ID_PING) { // if incoming packet is ping
                // Convert array -> int
                unsigned int value = (currentPacket.payLoad[1] << 24) |
                                        (currentPacket.payLoad[2] << 16) |
                                        (currentPacket.payLoad[3] << 8) |
                                        (currentPacket.payLoad[4]);
                
                value = value >> 1; // Divide by 2

                // int -> array
                unsigned char responsePayload[4];
                responsePayload[0] = (value >> 24) & 0xFF;
                responsePayload[1] = (value >> 16) & 0xFF;
                responsePayload[2] = (value >> 8) & 0xFF;
                responsePayload[3] = value & 0xFF;

                // Send PONG response
                Protocol_SendPacket(5, ID_PONG, responsePayload);
            }
            if (currentPacket.ID == ID_LEDS_SET) {  // if incoming packet is LED set
                LEDS_SET(currentPacket.payLoad[1]); // set LED
            }
            if (currentPacket.ID == ID_LEDS_GET) {  //if incoming packet is LED get
                unsigned char ledState = LEDS_GET(); // get LED state
                Protocol_SendPacket(2, ID_LEDS_STATE, &ledState);   // send LED state
            }
        }
    }
    
    return 0;
}
#endif
 

 

