// Note (13/06/2017): Updated Manchester library from github repository fails 
// when transmit data values above 767 (0x02FF), the receiver can't get the 
// packages. To avoid that, use the Manchester sources provided in this example.

#include "manchester.h"
#include "skipjack.c"

#define MY_ID 0x1B // Decimal value: 175 - One Byte, range (0-255) | (0x00-0xFF)
#define CMD 0xFF   // Decimal value: 255 - One Byte, range (0-255) | (0x00-0xFF)
#define P_TX 9     // Transmission digital pin
#define SKIPJ_KEY_SIZE 10
#define SKIPJ_BLOCK_SIZE 8

const uint8_t skipjack_key[SKIPJ_KEY_SIZE] = {0x00,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11};


uint8_t toEncodeData[SKIPJ_BLOCK_SIZE];

void setup()
{
    Serial.begin(9600);
    man.setupTransmit(P_TX, MAN_1200);
}

void loop()
{
    toEncodeData[0] = MY_ID;
    toEncodeData[1] = CMD;
    
    Serial.print("\nPackage to send:\n");
    Serial.print("ID - 0x");
    Serial.print(toEncodeData[0], HEX);
    Serial.print(" , Data (command) - 0x");
    Serial.print(toEncodeData[1], HEX);
    Serial.print("\n");

    skipjack_enc(toEncodeData, skipjack_key);
    man.transmitArray(SKIPJ_BLOCK_SIZE, toEncodeData);
    
    Serial.print("Package sent\n");
    Serial.print("\n");
    
    delay(1000);
}

