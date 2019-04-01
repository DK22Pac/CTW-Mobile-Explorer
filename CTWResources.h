/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#pragma once
#include "d3d9.h"
#include <stdio.h>

enum eResourceType {
    RESOURCE_UNDEFINED,
    RESOURCE_TEXTURE,
    RESOURCE_MODEL,
    RESOURCE_WORLDBLOCK,
    RESOURCE_DATA,
    RESOURCE_BINARY,
    RESOURCE_PALETTE,
    RESOURCE_TEXT,
    RESOURCE_RAW,
    RESOURCE_MP4
};

struct ModelVertex {
    short x, y, z;
    short nx, ny, nz;
    short u, v;
};

struct ModelMaterial {
    short texture;
    unsigned short vertexCount;
    unsigned char renderingFlags;
    unsigned char node;
    unsigned char unknown1;
    unsigned char unknown2;
    unsigned int varianceFlags;
};

struct ModelMatrix {
    short right_x, right_y, right_z;
    short top_x, top_y, top_z;
    short at_x, at_y, at_z;
    char parentNode;
    char unknown1;
    int x, y, z;
};

struct Matrix {
    short right_x, right_y, right_z;
    short top_x, top_y, top_z;
    short at_x, at_y, at_z;
    short padding;
    int x, y, z;
};

struct WorldSector {
    Matrix transform;
    unsigned short sectorOffsets[4];
};

struct SectorLevel {
    int x;
    int y;
    int z;
    unsigned short numInstances;
    unsigned short flags;
};

struct ModelInstance {
    short id;
    unsigned char renderListId;
    unsigned char buildingSwap;
    int resourceId;
    unsigned int offsetToMesh;
    void *ptr_unused;
};

struct Light {
    int a;
    int b;
    int c;
    int d;
    int e;
};

struct Unk20 {
    int a;
    int b;
    int c;
    int d;
    int e;
};

struct Sector {
    unsigned char bool1;
    unsigned char bool2;
    unsigned short numInstances; // 16b
    unsigned short numLights; // 20b - 2dfx
    unsigned short numLevels; // 16b - objs
    unsigned short count6; // 20b
    unsigned short numTextures; // 2b - texture IDs
    // SectorLevel levels[numLevels];
    // ModelInstance instances[numInstances];
    // Light lights[numLights];
    // Unk20 unk20[count6];
    // short textureIds[numTextures];
};

struct VehicleInfo {
    unsigned short vehicleType;
    short resourceId;
    unsigned int field_4;
    char name[32];
    char data[272];
};

struct Radar {
    short field_0;
    short field_2;
    unsigned short segments_x;
    unsigned short segments_y;
    // ids start here
    short fullmapId;
    short emptychunkId;
    short emptychunk2Id;

    // map chunks
    short _chunks;
};

static_assert(sizeof(ModelVertex) == 16, "Incorrect size of ModelVertex");
static_assert(sizeof(ModelMaterial) == 12, "Incorrect size of ModelMaterial");
static_assert(sizeof(ModelMatrix) == 32, "Incorrect size of ModelMatrix");
static_assert(sizeof(VehicleInfo) == 0x138, "Incorrect size of VehicleInfo");
static_assert(sizeof(WorldSector) == 40, "Incorrect size of WorldSector");
static_assert(sizeof(Sector) == 12, "Incorrect size of Sector");
static_assert(sizeof(SectorLevel) == 16, "Incorrect size of SectorLevel");
static_assert(sizeof(ModelInstance) == 16, "Incorrect size of ModelInstance");

struct ResourceModelHeader {
    char signature[2];
    unsigned short numVariances;
    unsigned char numMatrices;
    unsigned char numMaterials;
    unsigned short numVertices;
    unsigned int unknown1;
    unsigned int unknown2;
    unsigned int unknown3[8];
};

struct ResourceTextureHeader {
    unsigned short width;
    unsigned short height;
    unsigned short format;
    unsigned char depth;
    unsigned char hasAlpha;
    unsigned int pixelsSize;
};

struct chunk {
    short arr[16];
    int count;

    chunk();
    void add(short value);
};

struct sPakArchive {
    unsigned int versionSignature;
    unsigned int ranges[3];
    unsigned int resourcesCount; // or largest resource id?
    unsigned int resourceBlocksCount; // 4096b blocks
    // resources table [4072b]
    //@ [resourceBlocksCount * 4096]
    // resources tabe [4292b]

    unsigned int numVehicles;
    unsigned int fileSize;
    unsigned short *pResourceOffsets;

    unsigned int getResourceOffset(unsigned int resourceId);
    unsigned int getResourceSize(unsigned int resourceId);
    eResourceType GetResourceType(unsigned int resourceId, FILE *pakFile);
    void MapResourceNames(FILE *pakFile);
    void NodeGetInfo(char *nodeName, unsigned int *outId, unsigned int *outType, unsigned int *outOffset, char *outName);
};

struct sDxtPack {
    unsigned int offsets[8192];
    unsigned int sizes[8192];
};

struct sRomEntry {
    unsigned int hash;
    unsigned int offset;
    unsigned int size;
};

struct sRomPack {
    unsigned int numEntries;
    sRomEntry entries[4000];

    unsigned int GetHash(char *str);
    void MapResourceNames();
};

void GetTextureFormatName(unsigned int format, char *outName);
D3DFORMAT GetTextureFormatD3DFormat(unsigned int format, unsigned int depth);
D3DFORMAT GetTextureFormatD3DFormat_PNG(unsigned int format);
