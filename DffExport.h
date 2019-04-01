/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#pragma once
#include <stdio.h>
#include "dffapi\Clump.h"

namespace CWCONV{

struct CTWVertex {
    short x;
    short y;
    short z;
    short nx;
    short ny;
    short nz;
    short u;
    short v;
};

static_assert(sizeof(CTWVertex) == 16, "Incorrect size of CTWVertex");

struct CTWMatrix {
    short right_x, right_y, right_z;
    short top_x, top_y, top_z;
    short at_x, at_y, at_z;
    char parentNode;
	char unknown1;
    int x, y, z;
};

static_assert(sizeof(CTWMatrix) == 32, "Incorrect size of CTWMatrix");

struct CTWMaterial {
    short texture;
    unsigned short vertexCount;
    unsigned char renderingFlags;
    unsigned char node;
    unsigned char _pad[2];
    unsigned int varianceFlags;
};

static_assert(sizeof(CTWMaterial) == 12, "Incorrect size of CTWMaterial");

struct CTWModel {
    char signature[2]; // MG
    unsigned short numVariances;
    unsigned char numMatrices;
    unsigned char numMaterials;
    unsigned short numVertices;
    unsigned int unknown1;
    unsigned int unknown2;
	
	unsigned int unknown3[8];

    CTWVertex *vertices;
    CTWMatrix *matrices;
    CTWMaterial *materials;

	bool loaded;

    CTWModel(char const *filename);
    CTWModel(FILE *file);
    ~CTWModel();
};

class mesh {
public:
    static void clump_delete_empty_data(gtaRwClump *clump);
    static void geometry_calc_bound_sphere(gtaRwGeometry *geometry);
	// trilist
    static unsigned int get_trilist_tri_count(unsigned int num_verts);
    static void geometry_generate_trilist(gtaRwGeometry *geometry);
	// tristrip
    static void geometry_mesh_begin(gtaRwGeometry *geometry, unsigned int mesh_count);
    static void geometry_bind_mesh(gtaRwGeometry *geometry, unsigned int mesh, unsigned int vertex_at, unsigned int vertex_count, unsigned int material);
    static void geometry_mesh_end(gtaRwGeometry *geometry);
};
}

struct GeomInfo {
	unsigned int numMaterials;
	unsigned int numVertices;
	unsigned int currentVertex;
	unsigned int currentMesh;
	bool textured;
};

bool DoDffExport(FILE *globalFile, char *modelName, char *outputFileName);
