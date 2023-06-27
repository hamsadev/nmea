# nmeaSentence

A light library for parsing the parameters inside a NMEA sentence and detecting the parameter type.

## Dependencies
[Param](https://github.com/Ali-Mirghasemi/Param)<br>
[Str](https://github.com/Ali-Mirghasemi/Str)

## How to use
0. Prepare a NMEA sentence. Like:
```
char GGA_testSentence[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000,*5E";
```
1. Add nmea, Param and Str lib to your project
2. Include nmea.h
```
#include "nmea.h"
```

2. Create an instance of "NMEA_sentence" struct to hold the parser result
```
NMEA_sentence nmea;
```

3. Create an array of "NMEA_Field" to hold the parameters
```
NMEA_Field fields[GGA_fieldNum];
```

4. Use "NMEA_parseSentence" function to parse GGA_testSentence like this:
```
NMEA_LenType ret = NMEA_parseSentence(&nmea, &fields, GGA_fieldNum, GGA_testSentence);
```
5. If the output is smaller than 0, there is a problem in the parsing process, otherwise the result is the number of fields that have been parsed and saved.
6. You can find the details of the parsing operation through nmea

## License
[MIT](https://choosealicense.com/licenses/mit/)

## Docs
[NMEA Reference Manual-Rev2.1-Dec07](https://web.fe.up.pt/~ee95080/NMEA%20data.pdf)<br>
[NMEA data](https://www.sparkfun.com/datasheets/GPS/NMEA%20Reference%20Manual-Rev2.1-Dec07.pdf)
