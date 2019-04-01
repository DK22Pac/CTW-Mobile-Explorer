/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#pragma once
#include <map>

class namesMap {
public:
	std::map<unsigned int, std::string> map;

    bool thisIdHasMappedValue(unsigned int id) const;
    const char *getName(unsigned int id);
    void setName(unsigned int id, char *name);
    void clear();
};

extern namesMap modelNames;
