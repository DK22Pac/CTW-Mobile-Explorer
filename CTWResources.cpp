/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#include "CTWResources.h"
#include "ModelNameMap.h"

chunk::chunk() {
    count = 0;
}

void chunk::add(short value) {
    arr[count++] = value;
}

unsigned int sRomPack::GetHash(char * str) {
    int v2, v4, v5;
    v2 = *str;
    if (*str) {
        unsigned int v3 = 0;
        do {
            v4 = (unsigned __int8)(v2 - 32);
            if ((unsigned int)(v2 - 97) > 25)
                v4 = v2;
            v5 = (unsigned __int8)(str++)[1];
            v2 = v5;
            v3 = 1025 * (v3 + v4) ^ (1025 * (v3 + v4) >> 6);
        } while (v5);
        return 32769 * (9 * v3 ^ (9 * v3 >> 11));
    }
    return 0;
}

void sRomPack::MapResourceNames() {
    FILE *names = fopen("filenames.dat", "rt");
    if (!names)
        return;
    char line[512];
    while (fgets(line, 512, names)) {
        char name[512];
        name[0] = '\0';
        sscanf(line, "%s", name);
        if (*name != '\n' && *name != ' ' && *name != '\0') {
            if (!strchr(name, '.')) {
                char temp[512];
                strcpy(temp, "E_");
                strcat(temp, name);
                strcat(temp, ".gxt");
                strcpy(name, temp);
            }
            modelNames.setName(GetHash(name), name);
        }
    }
    fclose(names);
}

void GetTextureFormatName(unsigned int format, char *outName) {
    switch (format) {
    case 0x8363:
        strcpy(outName, "PIXEL_RGB");
        return;
    case 0xBEEF:
        strcpy(outName, "PIXEL_PNG_RGBA");
        return;
    case 0x83F0:
        strcpy(outName, "PIXEL_DXT1_RGB");
        return;
    case 0x83F3:
        strcpy(outName, "PIXEL_DXT5_RGBA");
        return;
    case 0x87EE:
        strcpy(outName, "PIXEL_ATC_RGBA");
        return;
    case 0x1900:
        strcpy(outName, "PIXEL_COLOR_INDEX");
        return;
    case 0x1901:
        strcpy(outName, "PIXEL_STENCIL_INDEX");
        return;
    case 0x1902:
        strcpy(outName, "PIXEL_DEPTH_COMPONENT");
        return;
    case 0x1903:
        strcpy(outName, "PIXEL_RED");
        return;
    case 0x1904:
        strcpy(outName, "PIXEL_GREEN");
        return;
    case 0x1905:
        strcpy(outName, "PIXEL_BLUE");
        return;
    case 0x1906:
        strcpy(outName, "PIXEL_ALPHA");
        return;
    case 0x1907:
        strcpy(outName, "PIXEL_RGB");
        return;
    case 0x1908:
        strcpy(outName, "PIXEL_RGBA");
        return;
    case 0x1909:
        strcpy(outName, "PIXEL_LUMINANCE");
        return;
    case 0x190A:
        strcpy(outName, "PIXEL_LUMINANCE_ALPHA");
        return;
    }
    if (format & 0x8000) {
        strcpy(outName, "PIXEL_PVRTC_RGBA");
        return;
    }
    sprintf(outName, "UNKNOWN (0x%X)", format);
    return;
}

D3DFORMAT GetTextureFormatD3DFormat(unsigned int format, unsigned int depth) {
    switch (format)
    {
    case 0x8363:
        if (depth == 16)
            return D3DFMT_X4R4G4B4;
        return D3DFMT_X8R8G8B8;
    case 0xBEEF:
        return D3DFMT_A8R8G8B8;
    case 0x83F0:
        return D3DFMT_DXT1;
    case 0x83F3:
        return D3DFMT_DXT5;
    case 0x87EE:
        return D3DFMT_A8R8G8B8;
    case 0x1900:
        return D3DFMT_INDEX32;
    case 0x1901:
        return D3DFMT_INDEX32;
    case 0x1902:
        return D3DFMT_INDEX32;
    case 0x1903:
        return D3DFMT_L8;
    case 0x1904:
        return D3DFMT_L8;
    case 0x1905:
        return D3DFMT_L8;
    case 0x1906:
        return D3DFMT_A8;
    case 0x1907:
        if (depth == 16)
            return D3DFMT_X4R4G4B4;
        return D3DFMT_X8R8G8B8;
    case 0x1908:
        if (depth == 16)
            return D3DFMT_A4R4G4B4;
        return D3DFMT_A8R8G8B8;
    case 0x1909:
        return D3DFMT_L8;
    case 0x190A:
        return D3DFMT_A8L8;
    }
    if (format & 0x8000)
        return D3DFMT_A8R8G8B8;
    return D3DFMT_X8R8G8B8;
}

D3DFORMAT GetTextureFormatD3DFormat_PNG(unsigned int format) {
    switch (format)
    {
    case 0x8363:
    case 0x83F0:
    case 0x1900:
    case 0x1901:
    case 0x1902:
    case 0x1903:
    case 0x1904:
    case 0x1905:
    case 0x1907:
    case 0x1909:
        return D3DFMT_X8R8G8B8;
    case 0xBEEF:
    case 0x83F3:
    case 0x87EE:
    case 0x1906:
    case 0x1908:
    case 0x190A:
        return D3DFMT_A8R8G8B8;
    }
    if (format & 0x8000)
        return D3DFMT_A8R8G8B8;
    return D3DFMT_X8R8G8B8;
}

unsigned int sPakArchive::getResourceOffset(unsigned int resourceId) {
    unsigned int offset = pResourceOffsets[resourceId] * 4096;
    if (resourceId >= ranges[0]) {
        if (resourceId >= ranges[1]) {
            if (resourceId >= ranges[2])
                offset += 0x30000000;
            else
                offset += 0x20000000;
        }
        else
            offset += 0x10000000;
    }
    return offset;
}

unsigned int sPakArchive::getResourceSize(unsigned int resourceId) {
    if (resourceId == (resourcesCount - 1))
        return fileSize - getResourceOffset(resourceId);
    return getResourceOffset(resourceId + 1) - getResourceOffset(resourceId);
}

eResourceType sPakArchive::GetResourceType(unsigned int resourceId, FILE * pakFile) {
    unsigned int offset = getResourceOffset(resourceId);
    fseek(pakFile, offset, SEEK_SET);
    char data[6];
    fread(data, 6, 1, pakFile);
    if (data[0] == 'M' && data[1] == 'G')
        return RESOURCE_MODEL;
    ResourceTextureHeader *texHeader = (ResourceTextureHeader *)data;
    if (texHeader->width <= 2048 && texHeader->height <= 2048 && texHeader->height > 1 && texHeader->width > 1) {
        if (texHeader->format == 0x8363 || texHeader->format == 0xBEEF ||
            texHeader->format == 0x83F0 || texHeader->format == 0x83F3 ||
            texHeader->format == 0x87EE || texHeader->format == 0x8C00 ||
            texHeader->format == 0x8C01 || texHeader->format == 0x8C02)
            return RESOURCE_TEXTURE;
        else {
            if (texHeader->format >= 0x1900 && texHeader->format <= 0x190A)
                return RESOURCE_TEXTURE;
        }
    }
    return RESOURCE_UNDEFINED;
}

void sPakArchive::MapResourceNames(FILE *pakFile) {
    unsigned int offset = getResourceOffset(0);
    fseek(pakFile, offset, SEEK_SET);
    short resTableIds[23];
    fread(resTableIds, 56, 1, pakFile);
    modelNames.setName(0, "maintable.res");
    if (resTableIds[0] != -1) {
        modelNames.setName(resTableIds[0], "worldstreamblocks.res");
        unsigned int offset = getResourceOffset(resTableIds[0]);
        fseek(pakFile, offset, SEEK_SET);
        fseek(pakFile, 8, SEEK_CUR);
        short blockIds[2478];
        fread(&blockIds, 2, 2478, pakFile);
        for (int i = 0; i < 2478; i++) {
            if (blockIds[i] != -1) {
                char name[32];
                sprintf(name, "worldblock%d.wbl", i);
                modelNames.setName(blockIds[i], name);
            }
        }
    }
    if (resTableIds[4] != -1) {
        modelNames.setName(resTableIds[4], "vehicleinfos.res");
        unsigned int offset = getResourceOffset(resTableIds[4]);
        fseek(pakFile, offset, SEEK_SET);
        fread(&numVehicles, 4, 1, pakFile);
        if (numVehicles > 0) {
            VehicleInfo *vehInfos = new VehicleInfo[numVehicles];
            fread(vehInfos, 0x138, numVehicles, pakFile);
            for (int i = 0; i < numVehicles; i++) {
                if (vehInfos[i].resourceId != -1) {
                    char vehname[40];
                    memcpy(vehname, vehInfos[i].name, 32);
                    vehname[32] = '\0';
                    if (strchr(vehname, '.'))
                        strchr(vehname, '.')[0] = '\0';
                    strcat(vehname, ".mdl");
                    modelNames.setName(vehInfos[i].resourceId, vehname);
                }
            }
            delete[] vehInfos;
        }
    }
    if (resTableIds[1] != -1)
        modelNames.setName(resTableIds[1], "globaltextures.res");
    if (resTableIds[2] != -1)
        modelNames.setName(resTableIds[2], "globalalphatextures.res");
    if (resTableIds[5] != -1)
        modelNames.setName(resTableIds[5], "vehiclepalettes.res");
    if (resTableIds[5] != -1)
        modelNames.setName(resTableIds[5], "vehiclepalettes.res");
    if (resTableIds[8] != -1)
        modelNames.setName(resTableIds[8], "pedinfos.res");
    if (resTableIds[19] != -1)
        modelNames.setName(resTableIds[19], "dynamiclights.res");
    if (resTableIds[22] != -1) {
        modelNames.setName(resTableIds[22], "radar.res");
        unsigned int offset = getResourceOffset(resTableIds[22]);
        fseek(pakFile, offset + 8, SEEK_SET);
        short texId;
        fread(&texId, 2, 1, pakFile);
        if (texId != -1)
            modelNames.setName(texId, "radarmap.tex");
        fseek(pakFile, 4, SEEK_CUR);
        short radarChunkIds[56]; // 8 x 7
        fread(&radarChunkIds, 2, 56, pakFile);
        for (int i = 0; i < 56; i++) {
            if (radarChunkIds[i] != -1) {
                char name[32];
                sprintf(name, "radar%02d.tex", i);
                modelNames.setName(radarChunkIds[i], name);
            }
        }
    }
}

void sPakArchive::NodeGetInfo(char * nodeName, unsigned int * outId, unsigned int * outType, unsigned int * outOffset, char * outName) {
    unsigned int id, type, offset;
    char resTypeName[32];
    char nn[256];
    strcpy(nn, nodeName);
    char *p = strstr(nn, ".");
    *p = '\0';
    if (outName)
        strcpy(outName, nn);
    sscanf(&p[1], "%s %*s %d %*s 0x%X", resTypeName, &id, &offset);
    if (outId)
        *outId = id;
    if (outType) {
        *outType = RESOURCE_UNDEFINED;
        switch (resTypeName[0]) {
        case 't':
            if (resTypeName[1] == 'e')
                *outType = RESOURCE_TEXTURE;
            break;
        case 'm':
            if (resTypeName[1] == 'd')
                *outType = RESOURCE_MODEL;
            else
                *outType = RESOURCE_MP4;
            break;
        case 'w':
            *outType = RESOURCE_WORLDBLOCK;
            break;
        case 'b':
            *outType = RESOURCE_BINARY;
            break;
        case 'd':
            *outType = RESOURCE_DATA;
            break;
        case 'p':
            *outType = RESOURCE_PALETTE;
            break;
        case 'g':
            *outType = RESOURCE_TEXT;
            break;
        }
    }
    if (outOffset)
        *outOffset = offset;
}
