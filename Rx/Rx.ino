// Note (13/06/2017): Updated Manchester library from github repository fails 
// when transmit data values above 767 (0x02FF), the receiver can't get the 
// packages. To avoid that, use the Manchester sources provided in this example.

#include "manchester.h"
#include "skipjack.c"

#define TX_DEVICE_ID 0x1B
#define CMD 0xFF
#define P_RX 4
#define SKIPJ_KEY_SIZE 10
#define SKIPJ_BLOCK_SIZE 8

const uint8_t skipjack_key[SKIPJ_KEY_SIZE] = {0x00,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11};

uint8_t toDecodeData[SKIPJ_BLOCK_SIZE];

void setup()
{
    Serial.begin(9600);
    man.setupReceive(P_RX, MAN_1200);
    man.beginReceiveArray(SKIPJ_BLOCK_SIZE, toDecodeData);
}

void loop()
{
    uint8_t id, cmd;
    
    if(man.receiveComplete())
    {
        skipjack_dec(toDecodeData, skipjack_key);
        id = toDecodeData[0];
        cmd = toDecodeData[1];

        man.beginReceiveArray(SKIPJ_BLOCK_SIZE, toDecodeData);
        
        Serial.print("\nPackage received:\n");
        Serial.print("ID - 0x");
        Serial.print(id, HEX);
        Serial.print(" , Data (command) - 0x");
        Serial.print(cmd, HEX);
        Serial.print("\n");
        
        if(id == TX_DEVICE_ID)
        {
            if(cmd == CMD)
            {
                Serial.print("Expected command from device [0x");
                Serial.print(TX_DEVICE_ID, HEX);
                Serial.print("] has been received\n");
            }
        }

        Serial.print("\n");
    }
}
