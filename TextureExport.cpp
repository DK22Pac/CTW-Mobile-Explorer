/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#include "TextureExport.h"
#include "CTWResources.h"
#include "dffapi\Stream.h"
#include "PVRTC/PVRTDecompress.h"
#include <stdlib.h>
#include <intrin.h>
#include "dffapi\texture_helper.h"
#include "d3dx9.h"

bool converter::initialised = false;

LPDIRECT3D9 g_pD3D;
LPDIRECT3DDEVICE9 pDevice;
D3DPRESENT_PARAMETERS d3dpp;

HRESULT DeviceCreate(HWND window) {
    g_pD3D = NULL;
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;
    pDevice = NULL;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &pDevice)))
        return E_FAIL;
    return D3D_OK;
}

void converter::init(HWND window) {
    initialised = false;
    if (DeviceCreate(window) != D3D_OK)
    {
        gtaRwErrorSet("Failed to create Direct3D device");
        return;
    }
    initialised = true;
}

IDirect3DTexture9 *converter::create_texture(unsigned int width, unsigned int height, D3DFORMAT format) {
    IDirect3DTexture9 *tex;
    if (D3DXCreateTexture(pDevice, width, height, 1, 0, format, D3DPOOL_MANAGED, &tex) == D3D_OK)
        return tex;
    return NULL;
}

IDirect3DTexture9 *converter::texture_change(IDirect3DTexture9 *texture, D3DFORMAT format) {
    ID3DXBuffer *buffer;
    D3DXSaveTextureToFileInMemory(&buffer, D3DXIFF_PNG, texture, NULL);
    texture->Release();
    texture = NULL;
    D3DXCreateTextureFromFileInMemoryEx(pDevice, buffer->GetBufferPointer(), buffer->GetBufferSize(),
        D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, format, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
        0, NULL, NULL, &texture);
    return texture;
}

void converter::destroy_texture(IDirect3DTexture9 * texture) {
    texture->Release();
}

void converter::save_texture(IDirect3DTexture9 *texture, char const *filename, D3DFORMAT format) {
    D3DXSaveTextureToFile(filename, D3DXIFF_PNG, texture, NULL);
}

unsigned int clz(unsigned int value) {
    DWORD leading_zero = 0;
    if (_BitScanReverse(&leading_zero, value))
        return 31 - leading_zero;
    else {
        // Same remarks as above
        return 32;
    }
}

bool IsPvrtcTexture(unsigned int format) {
    if (format == 0x87EE || format == 0x8363)
        return false;
    if (format & 0x8000)
        return true;
    return false;
}

void DecompressPvrtc(unsigned char *dest, void *src, ResourceTextureHeader& header) {
    int _2bitMode = clz((unsigned __int16)(header.format & 0xFFFD) - 0x8C01) >> 5;
    PVRTDecompressPVRTC(src, _2bitMode, header.width, header.height, dest);
    unsigned int numPixels = header.width * header.height;
    for (int i = 0; i < numPixels; i++) {
        unsigned char b = ((_rgba *)&dest[i * 4])->b;
        ((_abgr *)&dest[i * 4])->r = ((_rgba *)&dest[i * 4])->r;
        ((_abgr *)&dest[i * 4])->b = b;
    }
}

bool DoTextureExport(FILE *globalFile, char const *outputFileName, unsigned int resourceSize) {
    if (!converter::initialised)
        return false;
    ResourceTextureHeader header;
    fread(&header, 12, 1, globalFile);

    // PNG
    if (header.format == 0xBEEF) {
        char *data = new char[header.pixelsSize];
        fread(data, header.pixelsSize, 1, globalFile);
        FILE *file = fopen(outputFileName, "wb");
        fwrite(data, header.pixelsSize, 1, file);
        delete[] data;
        fclose(file);
        return true;
    }
    IDirect3DTexture9 *tex = converter::create_texture(header.width, header.height, GetTextureFormatD3DFormat(header.format, header.depth));
    unsigned char *pixels = new unsigned char[resourceSize];
    fread(pixels, resourceSize, 1, globalFile);
    D3DLOCKED_RECT rect;
    tex->LockRect(0, &rect, NULL, 0);
    unsigned int size = 0;
    switch (header.format) {
        // DXT 1
    case 0x83F0:
        size = 4 * header.height * header.width;
        memcpy(rect.pBits, pixels, size / 8);
        break;
        // DXT 5
    case 0x83F3:
        size = 8 * header.height * header.width;
        memcpy(rect.pBits, pixels, size / 8);
        break;
    default:
        if (IsPvrtcTexture(header.format))
            DecompressPvrtc((unsigned char *)rect.pBits, pixels, header);
        else {
            size = header.pixelsSize;
            memcpy(rect.pBits, pixels, size);
        }
        break;
    }
    tex->UnlockRect(0);
    converter::save_texture(tex, outputFileName, GetTextureFormatD3DFormat_PNG(header.format));
    delete[] pixels;
    converter::destroy_texture(tex);
    return true;
}

bool GetTexturePixels(FILE *globalFile, unsigned int resourceSize, char **pPixels, unsigned int *width, unsigned int *height, bool *hasAlpha) {
    if (!converter::initialised)
        return false;
    ResourceTextureHeader header;
    fread(&header, 12, 1, globalFile);
    IDirect3DTexture9 *tex = NULL;
    // PNG
    if (header.format == 0xBEEF) {
        char *data = new char[header.pixelsSize];
        fread(data, header.pixelsSize, 1, globalFile);
        D3DXCreateTextureFromFileInMemory(pDevice, data, header.pixelsSize, &tex);
        delete[] data;
    }
    else {
        tex = converter::create_texture(header.width, header.height, GetTextureFormatD3DFormat(header.format, header.depth));
        unsigned char *pixels = new unsigned char[resourceSize];
        fread(pixels, resourceSize, 1, globalFile);
        D3DLOCKED_RECT rect;
        tex->LockRect(0, &rect, NULL, 0);
        unsigned int size = 0;
        switch (header.format) {
            // DXT 1
        case 0x83F0:
            size = 4 * header.height * header.width;
            memcpy(rect.pBits, pixels, size / 8);
            break;
            // DXT 5
        case 0x83F3:
            size = 8 * header.height * header.width;
            memcpy(rect.pBits, pixels, size / 8);
            break;
        default:
            if (IsPvrtcTexture(header.format))
                DecompressPvrtc((unsigned char *)rect.pBits, pixels, header);
            else {
                size = header.pixelsSize;
                memcpy(rect.pBits, pixels, size);
            }
            break;
        }
        tex->UnlockRect(0);
        delete[] pixels;
    }
    IDirect3DSurface9 *surface;
    tex->GetSurfaceLevel(0, &surface);
    D3DSURFACE_DESC desc;
    surface->GetDesc(&desc);
    surface->Release();
    if (desc.Format != D3DFMT_A8B8G8R8 && desc.Format != D3DFMT_X8B8G8R8) {
        if (header.hasAlpha)
            tex = converter::texture_change(tex, D3DFMT_A8B8G8R8);
        else
            tex = converter::texture_change(tex, D3DFMT_X8B8G8R8);
    }
    tex->GetSurfaceLevel(0, &surface);
    surface->GetDesc(&desc);
    surface->Release();
    *hasAlpha = header.hasAlpha;
    *width = desc.Width;
    *height = desc.Height;

    D3DLOCKED_RECT lockrect;
    tex->LockRect(0, &lockrect, NULL, 0);
    *pPixels = new char[desc.Width * desc.Height * 4];
    memcpy(*pPixels, lockrect.pBits, desc.Width * desc.Height * 4);
    tex->UnlockRect(0);
    converter::destroy_texture(tex);
    return true;
}
