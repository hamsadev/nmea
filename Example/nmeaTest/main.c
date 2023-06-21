#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "nmea.h"

char GGA_testSentence[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,0,0000*5E";

int main (void){
    NMEA_sentence nmea;
    NMEA_Field fields[GGA_fieldNum];

    NMEA_result ret = NMEA_parseSentence(&nmea, &fields, GGA_fieldNum, GGA_testSentence);
    printf("ret: %d, talker: %d, type: %d\r\n", ret, nmea.header.talker, nmea.header.type);

    return 0;
}
