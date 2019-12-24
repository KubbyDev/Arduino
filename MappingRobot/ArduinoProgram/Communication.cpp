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

// Sends a chunck of the intern map to the ESP8266
// A chunck contains the data for lines 3*index to 3*(index+1)-1
void sendMapChunckToEsp(int chunckIndex) {

    char* chunck = (char*) malloc(sizeof(char)*3*9*3);
    int firstByte = chunckIndex*9*3;
    for(int i = 0; i < 3*9; i++) {
        unsigned char uc = bm_getByte(internMap, i + firstByte);
        chunck[i*3 +0] = uc/100;
        chunck[i*3 +1] = (uc%100)/10;
        chunck[i*3 +2] = uc%10;
    }

    for(int i = 0; i < 3*9*3; i++)
        SERIALOBJECT.write(chunck[i]);
    SERIALOBJECT.write('\n');

    free(chunck);
}

void initCommunication() {
    SERIALOBJECT.begin(57600);
}

void updateCommunication() {

    // If no command is received, does nothing
    if(! SERIALOBJECT.available())
        return;

    char commandType = SERIALOBJECT.read();
    // If a new target position is received, updates it
    // Target position update commands are of this form: T<POSX>,<POSY>\n
    if(commandType == 'T')
        vectorSet(target, readIntFromSerial(','), readIntFromSerial('\n'));
    // If a map chunck is requested, sends it
    // Map chunck requests are of this form: M<CHUNCKINDEX>\n
    if(commandType == 'M')
        sendMapChunckToEsp(readIntFromSerial('\n'));
}
