/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#include "ModelNameMap.h"

namesMap modelNames;

bool namesMap::thisIdHasMappedValue(unsigned int id) const {
    return map.end() != map.find(id);
}

const char *namesMap::getName(unsigned int id) {
    if (thisIdHasMappedValue(id))
        return map[id].c_str();
    return nullptr;
}

void namesMap::setName(unsigned int id, char *name) {
    map[id] = name;
}

void namesMap::clear() {
    map.clear();
}
