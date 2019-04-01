/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#include <string.h>
#include "GXT.h"

cGXTFile::cGXTFile(unsigned char * data) {
    if (!strncmp((char *)data, "DS_GXT", 6)) {
        stringCount = *(unsigned short *)&data[6];
        if (stringCount > 0) {
            strings = new char *[stringCount];
            unsigned char *pStrings = &data[8];
            for (int i = 0; i < stringCount; i++) {
                unsigned short strLength = *(unsigned short *)&pStrings[0];
                pStrings += 2;
                unsigned short newStrLength = 0;
                for (int c = 0; c < strLength; c++) {
                    if (pStrings[c * 2 + 1] > 0xF0) {
                        unsigned char value = pStrings[c * 2];
                        switch (value) {
                        case 0:
                            newStrLength += 3;
                            break;
                        case 3:
                            newStrLength += 3;
                            break;
                        case 6:
                            newStrLength += 3;
                            break;
                        case 9:
                            newStrLength += 3;
                            break;
                        case 12:
                            newStrLength += 3;
                            break;
                        default:
                            newStrLength += 7;
                        }
                    }
                    else if (pStrings[c * 2 + 1] == 0 && pStrings[c * 2] == 0xA)
                        newStrLength += 3;
                    else
                        newStrLength += 1;
                }
                strings[i] = new char[newStrLength];
                unsigned int strCounter = 0;
                for (int c = 0; c < strLength; c++) {
                    if (pStrings[c * 2 + 1] > 0xF0) {
                        strings[i][strCounter] = '~';
                        unsigned char value = pStrings[c * 2];
                        char tmp[8];
                        switch (value) {
                        case 0:
                            strings[i][strCounter + 1] = 'w';
                            strings[i][strCounter + 2] = '~';
                            strCounter += 3;
                            break;
                        case 3:
                            strings[i][strCounter + 1] = 'r';
                            strings[i][strCounter + 2] = '~';
                            strCounter += 3;
                            break;
                        case 6:
                            strings[i][strCounter + 1] = 'g';
                            strings[i][strCounter + 2] = '~';
                            strCounter += 3;
                            break;
                        case 9:
                            strings[i][strCounter + 1] = 'b';
                            strings[i][strCounter + 2] = '~';
                            strCounter += 3;
                            break;
                        case 12:
                            strings[i][strCounter + 1] = 'y';
                            strings[i][strCounter + 2] = '~';
                            strCounter += 3;
                            break;
                        default:
                            strings[i][strCounter + 1] = '#';
                            if (value > 0xF)
                                sprintf(tmp, "%X%X", pStrings[c * 2 + 1], value);
                            else
                                sprintf(tmp, "%X0%X", pStrings[c * 2 + 1], value);
                            strings[i][strCounter + 2] = tmp[0];
                            strings[i][strCounter + 3] = tmp[1];
                            strings[i][strCounter + 4] = tmp[2];
                            strings[i][strCounter + 5] = tmp[3];
                            strings[i][strCounter + 6] = '~';
                            strCounter += 7;
                        }
                    }
                    else if (pStrings[c * 2 + 1] == 0 && pStrings[c * 2] == 0xA) {
                        strings[i][strCounter] = '~';
                        strings[i][strCounter + 1] = 'n';
                        strings[i][strCounter + 2] = '~';
                        strCounter += 3;
                    }
                    else {
                        strings[i][strCounter] = (char)pStrings[c * 2];
                        strCounter += 1;
                    }
                }
                strings[i][newStrLength] = '\0';
                pStrings += strLength * 2;
            }
        }
        else
            strings = 0;
        loaded = true;
    }
    else
    {
        strings = 0;
        stringCount = 0;
        loaded = false;
    }
}

cGXTFile::~cGXTFile() {
    delete[] strings;
}

void cGXTFile::Flush(char * outputFilePath) {
    FILE *file = fopen(outputFilePath, "wt");
    for (int i = 0; i < stringCount; i++) {
        fputs(strings[i], file);
        fputs("\n", file);
    }
    fclose(file);
}
