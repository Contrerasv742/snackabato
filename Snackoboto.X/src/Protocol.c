#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h> // Include stdio.h for //prinft

#include "Protocol2.h"
#include "uart.h"
#include <string.h>
#include "MessageIDs.h"


#define MIN_BAUDRATE 9600
#define MAX_BAUDRATE 115200

static PacketBuffer_t packetBuffer; // init packet buffer
static Packet_t Rxpacket; // Declare Rxpacket
extern circularBuffer rxBuffer; // Declare rxBuffer

typedef enum {
    WAIT_FOR_HEAD,
    WAIT_FOR_LENGTH,
    WAIT_FOR_ID,
    WAIT_FOR_PAYLOAD,
    WAIT_FOR_TAIL,
    WAIT_FOR_CHECKSUM,
    WAIT_FOR_END1,
    WAIT_FOR_END2
} PacketState_t;

static PacketState_t packetState;   // init packet state
static uint8_t calculatedChecksum; // init checksum
static int payloadIndex; // init payload index

/**
* @Function Protocol_Init(baudrate)
* @param Legal Uart baudrate
* @return SUCCESS (true) or ERROR (false)
* @brief Initializes Uart1 for stream I/O to the lab PC via a USB
* virtual comm port. Baudrate must be a legal value.
* @author instructor W2022 */
int Protocol_Init(unsigned long baudrate) {
    // Initialize packet buffer
    packetBuffer.head = 0;
    packetBuffer.tail = 0;
    packetBuffer.count = 0;

    //check baud rate legality
    if (!(MIN_BAUDRATE <= baudrate && baudrate <= MAX_BAUDRATE)) {
        return 0;
    } else {
        Uart_Init(baudrate);    // initialize UART w/ baudrate
        return 1;
    }
}

/**
* @Function unsigned char Protocol_QueuePacket()
* @param none
* @return the buffer full flag: 1 if full
* @brief Place in the main event loop (or in a timer) to continually check
* for completed incoming packets and then queue them into
* the RX circular buffer. The buffer's size is set by constant
* PACKETBUFFERSIZE.
* @author instructor W2023 */
uint8_t Protocol_QueuePacket() {
    Packet_t currentPacket;  // temp storage for incoming packet

    // incoming packet is built
    while (BuildRxPacket(&currentPacket, 0)) {
        // if incoming packet is led set
        if (currentPacket.ID == ID_LEDS_SET) {
            LEDS_SET(currentPacket.payLoad[0]); // set LEDs
        } 
        //if incoming packet is LED get
        else if (currentPacket.ID == ID_LEDS_GET) {
            unsigned char ledState = LEDS_GET();    // get led state
            Protocol_SendPacket(1,  ID_LEDS_STATE, &ledState);  // send packet led state
            return 0;  
        }

        // Check if the buffer is full
        uint8_t nextTail = (packetBuffer.tail + 1) % PACKETBUFFERSIZE;
        if (nextTail == packetBuffer.head) {
            return 1;
        }

        // Copy the packet to the buffer
        packetBuffer.buffer[packetBuffer.tail] = currentPacket;
        packetBuffer.tail = nextTail;
        packetBuffer.count++;

        return 0;

    }
    return 0;
}

/**
* @Function int Protocol_GetInPacket(uint8_t *type, uint8_t *len, unsigned char *msg)
* @param *type, *len, *msg
* @return SUCCESS (true) or WAITING (false)
* @brief Reads the next packet from the packet Buffer
* @author instructor W2022 */
int Protocol_GetInPacket(uint8_t *type, uint8_t *len, unsigned char *msg) {
    //prinft("\n##In Protocol_GetInPacket##\n");
    
    // Check if bufferempty
    if (packetBuffer.count == 0) {
        return 0;
    }

    // get packet from head of buffer
    Packet_t *packet = &packetBuffer.buffer[packetBuffer.head];

    // get packet info
    *type = packet->ID;
    *len = packet->len;

    // copy msg data
    for (uint8_t i = 0; i < *len; i++) {
        msg[i] = packet->payLoad[i];
    }

    // set buffer head
    packetBuffer.head = (packetBuffer.head + 1) % PACKETBUFFERSIZE;
    packetBuffer.count--;

    return 1;
}

/**
* @Function int Protocol_SendDebugMessage(char *Message)
* @param Message, Proper C string to send out
* @return SUCCESS (true) or ERROR (false)
* @brief Takes in a proper C-formatted string and sends it out using ID_DEBUG
* @warning this takes an array, do <b>NOT</b> call sprintf as an argument.
* @author mdunne */
int Protocol_SendDebugMessage(char *Message) {
    unsigned char len = 0;

    // check for null message
    if (Message == NULL) {
        return 0; // ERROR
    }

    // ensure message length does not exceed max payload length
    while (len < MAXPAYLOADLENGTH && Message[len] != '\0') {
        len++;
    }

    // send packet
    Protocol_SendPacket(len, ID_DEBUG, Message);
    return 1;
}

/**
* @Function int Protocol_SendPacket(unsigned char len, unsigned char ID, void *Payload)
* @param len, length of full <b>Payload</b> variable
* @param Payload, pointer to data
* @return SUCCESS (true) or ERROR (false)
* @brief composes and sends a full packet
* @author instructor W2022 */
int Protocol_SendPacket(unsigned char len, unsigned char ID, unsigned char *Payload) {
    unsigned char checksum = ID; // init checksum
    PutChar(HEAD);
    PutChar(len);
    PutChar(ID);    // packet ID
    //Send payload and update checksum
    printf("Sending: %02X %02X %02X", HEAD, len, ID); // debugging
    for (int i = 0; i < len-1; i++) {
        printf(" %02X", Payload[i]);    //debug
        PutChar(Payload[i]);
        checksum = Protocol_CalcIterativeChecksum(Payload[i], checksum);
    }
    printf("\n");   //debug
    PutChar(TAIL);
    PutChar(checksum);
    PutChar(PACKET_END1);
    PutChar(PACKET_END2);
}

/**
@Function unsigned char Protocol_ReadNextID(void)
* @param None
* @return Reads the ID of the next available Packet
* @brief Returns ID or 0 if no packets are available
* @author instructor W2022 */
unsigned char Protocol_ReadNextPacketID(void) {
    // check if buffer is empty
    if (packetBuffer.count == 0) {
        return 0;
    }

    // get packet from head of buffer
    Packet_t *packet = &packetBuffer.buffer[packetBuffer.head];

    // send packet
    return packet->ID;
}

/**
* @Function flushPacketBuffer()
* @param none
* @return none
* @brief flushes the rx packet circular buffer
* @author instructor W2022 */
void flushPacketBuffer (void) {
    packetBuffer.head = 0;
    packetBuffer.tail = 0;
    packetBuffer.count = 0;
}

/**
* @Function convertEndian(unsigned int *value)
* @param value, pointer to the unsigned int to convert
* @return none
* @brief converts the endian of the unsigned int
* @author 
*/
unsigned int convertEndian(unsigned int *value) {
    unsigned int temp = *value;
    *value = ((temp >> 24) & 0xFF) |
             ((temp >> 8) & 0xFF00) |
             ((temp << 8) & 0xFF0000) |
             ((temp << 24) & 0xFF000000);
    return *value;
}

uint8_t BuildRxPacket(Packet_t *rxPacket, unsigned char reset) {
    uint8_t byte;

    if (reset) { //reset condition
        flushPacketBuffer(); //clear packet buffer when reset
        packetState = WAIT_FOR_HEAD;
        return 0;
    }

    while (dequeue(&rxBuffer, &byte)) { //read from packet buffer
        //ignore bytes until the HEAD byte (0xCC) is found
        if (packetState == WAIT_FOR_HEAD && byte != 0xCC) {
            continue;
        }

        switch (packetState) {
            case WAIT_FOR_HEAD:
               //prinft("BuildRxPacket: Waiting for head\n");
               //prinft("Byte: %x\n", byte);
                if (byte == 0xCC) { //start of a new packet
                    rxPacket->ID = 0;
                    rxPacket->len = 0;
                    rxPacket->checkSum = 0;
                    payloadIndex = 0;
                    calculatedChecksum = 0;
                    memset(rxPacket->payLoad, 0, MAXPAYLOADLENGTH); // Clear payload array
                    packetState = WAIT_FOR_LENGTH;
                }
                break;

            case WAIT_FOR_LENGTH:
               //prinft("Byte: %x\n", byte);
                if (byte <= MAXPAYLOADLENGTH) {
                    rxPacket->len = byte; // Include ID byte in length
                    packetState = WAIT_FOR_ID;
                } else {
                    //invalid length - reset
                    flushPacketBuffer();
                    packetState = WAIT_FOR_HEAD;
                }
                break;

            case WAIT_FOR_ID:
               //prinft("BuildRxPacket: Waiting for ID\n");
               //prinft("Payload Index: %d\n", payloadIndex);
               //prinft("Length: %d\n", rxPacket->len);
               //prinft("Byte: %x\n", byte);
                rxPacket->ID = byte;
                rxPacket->payLoad[payloadIndex++] = byte; // Include ID in payload

               //prinft("Payload: ");
                for (int i = 0; i < rxPacket->len; i++) {
                   //prinft("%02X ", rxPacket->payLoad[i]);
                }
               //prinft("\n");

                calculatedChecksum = Protocol_CalcIterativeChecksum(byte, 0);
                packetState = (rxPacket->len > 1) ? WAIT_FOR_PAYLOAD : WAIT_FOR_TAIL;
                break;

            case WAIT_FOR_PAYLOAD:
               //prinft("BuildRxPacket: Waiting for Payload\n");
               //prinft("Payload Index: %d\n", payloadIndex);
               //prinft("Length: %d\n", rxPacket->len);
               //prinft("Checksum: %0x\n", calculatedChecksum);
               //prinft("Byte: %x\n", byte);
                
                if (payloadIndex >= MAXPAYLOADLENGTH) {
                    //buffer overflow - reset
                    flushPacketBuffer();
                    packetState = WAIT_FOR_HEAD;
                    break;
                }

                rxPacket->payLoad[payloadIndex++] = byte;
                calculatedChecksum = Protocol_CalcIterativeChecksum(byte, calculatedChecksum);

               //prinft("Payload: ");
                for (int i = 0; i < rxPacket->len; i++) {
                   //prinft("%02X ", rxPacket->payLoad[i]);
                }
               //prinft("\n");

                if (payloadIndex == rxPacket->len) {
                    packetState = WAIT_FOR_TAIL;
                }
                break;

            case WAIT_FOR_TAIL:
               //prinft("Payload: ");
                for (int i = 0; i < rxPacket->len; i++) {
                   //prinft("%02X ", rxPacket->payLoad[i]);
                }
               //prinft("\n");
                //prinft("BuildRxPacket: Waiting for Tail\n");
                //prinft("Byte: %x\n", byte);
                if (byte == 0xB9) {
                    packetState = WAIT_FOR_CHECKSUM;
                } else {
                    //invalid tail byte - reset
                    flushPacketBuffer();
                    packetState = WAIT_FOR_HEAD;
                }
                break;

            case WAIT_FOR_CHECKSUM:
                //prinft("BuildRxPacket: Waiting for Checksum\n");
                
                //prinft("Received checksum byte: %02X\n", byte);
                //prinft("Calculated checksum: %02X\n", calculatedChecksum);
                //prinft("Payload used for checksum calculation: ");
                for (int i = 0; i < rxPacket->len; i++) {
                    //prinft("%02X ", rxPacket->payLoad[i]);
                }
                //prinft("\n");

                calculatedChecksum = 0;
                for (int i = 0; i < rxPacket->len; i++) {
                    //prinft("Before: Byte: %02X, Checksum: %02X\n", rxPacket->payLoad[i], calculatedChecksum);
                    calculatedChecksum = Protocol_CalcIterativeChecksum(rxPacket->payLoad[i], calculatedChecksum);
                    //prinft("After: Byte: %02X, Updated Checksum: %02X\n", rxPacket->payLoad[i], calculatedChecksum);
                }
                
                //prinft("Byte: %x\n", byte);
                //prinft("Checksum: %0x\n", calculatedChecksum);
                if (byte == calculatedChecksum) {
                    rxPacket->checkSum = byte;
                    packetState = WAIT_FOR_END1;
                } else {
                    //checksum mismatch - reset
                    //prinft("checksum mismatch!!!\n");
                    flushPacketBuffer();
                    packetState = WAIT_FOR_HEAD;
                }
                break;

            case WAIT_FOR_END1:
                //prinft("BuildRxPacket: Waiting for End1\n");
                //prinft("Byte: %x\n", byte);
                if (byte == 0x0D) {
                    packetState = WAIT_FOR_END2;
                } else {
                    //missing end byte - reset
                    flushPacketBuffer();
                    packetState = WAIT_FOR_HEAD;
                }
                break;

            case WAIT_FOR_END2:
                //prinft("BuildRxPacket: Waiting for End2\n");
                //prinft("Byte: %x\n", byte);
                if (byte == 0x0A) {
                    packetState = WAIT_FOR_HEAD;
                    return 1; //packet successfully received
                } else {
                    //incorrect end byte - reset
                    flushPacketBuffer();
                    packetState = WAIT_FOR_HEAD;
                }
                break;
        }
    }
    return 0; //still waiting for more bytes
}

/**
* @Function char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned
char curChecksum)
* @param charIn, new char to add to the checksum
* @param curChecksum, current checksum, most likely the last return of this
function, can use 0 to reset
* @return the new checksum value
* @brief Returns the BSD checksum of the char stream given the curChecksum and the
new char
* @author mdunne */
unsigned char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char curChecksum) {
    curChecksum = ((curChecksum >> 1) | (curChecksum << 7)) & 0xFF; // Ensure 8-bit wraparound
    curChecksum = (curChecksum + charIn) & 0xFF;  // Constrain to 8-bit
    return curChecksum;      // Return the updated checksum
}


