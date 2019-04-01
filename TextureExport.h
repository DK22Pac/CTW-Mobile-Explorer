/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#pragma once
#include <stdio.h>
#include "d3d9.h"

class converter {
public:
	static bool initialised;

    static void init(HWND window);
    static IDirect3DTexture9 *create_texture(unsigned int width, unsigned int height, D3DFORMAT format);
    static IDirect3DTexture9 *texture_change(IDirect3DTexture9 *texture, D3DFORMAT format);
    static void destroy_texture(IDirect3DTexture9 *texture);
    static void save_texture(IDirect3DTexture9 *texture, char const *filename, D3DFORMAT format);
};

struct _abgr {
    unsigned char b, g, r, a;
};

struct _rgba {
    unsigned char r, g, b, a;
};

bool DoTextureExport(FILE *globalFile, char const *outputFileName, unsigned int resourceSize);
bool GetTexturePixels(FILE *globalFile, unsigned int resourceSize, char **pPixels, unsigned int *width, unsigned int *height, bool *hasAlpha);
