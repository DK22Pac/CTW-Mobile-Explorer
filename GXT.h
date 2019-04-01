/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#pragma once
#include <stdio.h>
#include "dffapi\Stream.h"

#define TAG_NOT_A_TAG 7FFFFFFF

enum eTextColour {
	TEXT_WHITE = 0,
	TEXT_BLUE = 9,
	TEXT_YELLOW = 18
};

struct gxt_file {
	char signature[6]; // "DS_GXT"
	unsigned short numStrings;
	// strings...
	// unsigned short numSymbols;
	// wchar_t symbols[numSymbols];
	// wchar_t terminatingNull;
	// ...
};

class cGXTFile {
public:
	bool loaded;
	unsigned short stringCount;
	char **strings;

    cGXTFile(unsigned char *data);
    ~cGXTFile();
    void Flush(char *outputFilePath);
};
