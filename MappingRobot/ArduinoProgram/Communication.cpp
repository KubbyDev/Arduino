#include "Data.h"
#include "Communication.h"

#include <Arduino.h>
#include <stdlib.h>

#define SERIALOBJECT Serial3 //The serial object used to communicate with the ESP8266

// Reads Serial input until endCharacter is reached, 
// then returns the int represented by the read input
int readIntFromSerial(char endCharacter) {
    char* res = (char*) malloc(sizeof(char)*10);
    char next = SERIALOBJECT.read();
    int index = 0;
    while(next != endCharacter) {
        res[index] = next;
        index++;
        next = SERIALOBJECT.read();
    }
    res[index] = 0;
    int result = atoi(res);
    free(res);
    return result;
}

// Sends a chunk of the intern map to the ESP8266
// A chunk contains the data for lines 3*index to 3*(index+1)-1
void sendMapChunkToEsp(int chunkIndex) {

    Serial.print("Received chunk request ");Serial.print(chunkIndex);Serial.print("\n");

    char* chunk = (char*) malloc(sizeof(char)*3*9*3 + 2);
    int firstByte = chunkIndex*9*3;
    for(int i = 0; i < 3*9; i++) {
        unsigned char uc = bm_getByte(internMap, i + firstByte);
        chunk[i*3 +0] = '0' + uc/100;
        chunk[i*3 +1] = '0' + (uc%100)/10;
        chunk[i*3 +2] = '0' + uc%10;
    }

    chunk[3*9*3] = '\n';
    chunk[3*9*3+1] = 0;
    SERIALOBJECT.write(chunk, 3*9*3+1);

    Serial.print("Responded ");Serial.print(chunk);

    free(chunk);
}

void initCommunication() {
    SERIALOBJECT.begin(57600);
}

void updateCommunication() {

    // If no command is received, does nothing
    if(! SERIALOBJECT.available())
        return;

    // Waits a bit just to be sure that the data has been written entirely
    delay(10);

    char commandType = SERIALOBJECT.read();
    // If a new target position is received, updates it
    // Target position update commands are of this form: T<POSX>,<POSY>\n
    if(commandType == 'T')
        vectorSet(target, readIntFromSerial(','), readIntFromSerial('\n'));
    // If a map chunk is requested, sends it
    // Map chunk requests are of this form: M<CHUNKINDEX>\n
    if(commandType == 'M')
        sendMapChunkToEsp(readIntFromSerial('\n'));
}
