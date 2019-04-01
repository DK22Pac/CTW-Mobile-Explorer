/*
/* GTA Chinatown Wars Mobile Explorer
/* https://github.com/DK22Pac/CTW-Mobile-Explorer
/* 2014-2019
*/
#include "DffExport.h"
#include "dffapi/Memory.h"

CWCONV::CTWModel::CTWModel(char const * filename) {
    FILE *file = fopen(filename, "rb");
    fread(&signature, 2, 1, file);
    if (signature[0] == 'M' && signature[1] == 'G') {
        fread(&numVariances, 46, 1, file);
        if (numVertices > 0) {
            vertices = new CTWVertex[numVertices];
            fread(vertices, sizeof(CTWVertex), numVertices, file);
        }
        if (numMatrices > 1) {
            matrices = new CTWMatrix[numMatrices - 1];
            fread(matrices, sizeof(CTWMatrix), numMatrices - 1, file);
        }
        if (numMaterials > 0) {
            materials = new CTWMaterial[numMaterials];
            fread(materials, sizeof(CTWMaterial), numMaterials, file);
        }
        loaded = true;
    }
    else
        loaded = false;
    fclose(file);
}

CWCONV::CTWModel::CTWModel(FILE * file) {
    fread(&signature, 2, 1, file);
    if (signature[0] == 'M' && signature[1] == 'G') {
        fread(&numVariances, 46, 1, file);
        if (numVertices > 0) {
            vertices = new CTWVertex[numVertices];
            fread(vertices, sizeof(CTWVertex), numVertices, file);
        }
        if (numMatrices > 1) {
            matrices = new CTWMatrix[numMatrices - 1];
            fread(matrices, sizeof(CTWMatrix), numMatrices - 1, file);
        }
        if (numMaterials > 0) {
            materials = new CTWMaterial[numMaterials];
            fread(materials, sizeof(CTWMaterial), numMaterials, file);
        }
        loaded = true;
    }
    else
        loaded = false;
}

CWCONV::CTWModel::~CTWModel() {
    if (numVertices > 0)
        delete[] vertices;
    if (numMatrices > 1)
        delete[] matrices;
    if (numMaterials > 0)
        delete[] materials;
}

void CWCONV::mesh::clump_delete_empty_data(gtaRwClump * clump) {
    unsigned int *newGeomIds = new unsigned int[clump->geometryList.geometryCount];
    unsigned int newGeomCount = 0;
    for (int i = 0; i < clump->geometryList.geometryCount; i++) {
        if (clump->geometryList.geometries[i].numVertices > 0) {
            newGeomIds[i] = newGeomCount;
            newGeomCount++;
        }
    }
    gtaRwGeometry *newGeometries = (gtaRwGeometry *)gtaMemAlloc(sizeof(gtaRwGeometry) * newGeomCount);
    gtaRwAtomic *newAtomics = (gtaRwAtomic *)gtaMemAlloc(sizeof(gtaRwAtomic) * newGeomCount);
    for (int i = 0; i < clump->geometryList.geometryCount; i++) {
        if (clump->geometryList.geometries[i].numVertices != 0) {
            clump->atomics[i].geometryIndex = newGeomIds[i];
            gtaMemCopy(&newGeometries[newGeomIds[i]], &clump->geometryList.geometries[i], sizeof(gtaRwGeometry));
            gtaMemCopy(&newAtomics[newGeomIds[i]], &clump->atomics[i], sizeof(gtaRwAtomic));
        }
    }
    delete[] newGeomIds;
    gtaMemFree(clump->geometryList.geometries);
    gtaMemFree(clump->atomics);
    clump->geometryList.geometries = newGeometries;
    clump->atomics = newAtomics;
    clump->geometryList.geometryCount = newGeomCount;
    clump->numAtomics = newGeomCount;
}

void CWCONV::mesh::geometry_calc_bound_sphere(gtaRwGeometry * geometry) {
    for (int i = 0; i < geometry->numMorphTargets; i++) {
        if (geometry->morphTarget[i].hasVerts) {
            gtaRwV3d min, max;
            min.x = min.y = min.z = 9999.0f;
            max.x = max.y = max.z = -9999.0f;
            for (int j = 0; j < geometry->numVertices; j++) {
                if (geometry->morphTarget[i].verts[j].x < min.x)
                    min.x = geometry->morphTarget[i].verts[j].x;
                if (geometry->morphTarget[i].verts[j].y < min.y)
                    min.y = geometry->morphTarget[i].verts[j].y;
                if (geometry->morphTarget[i].verts[j].z < min.z)
                    min.z = geometry->morphTarget[i].verts[j].z;
                if (geometry->morphTarget[i].verts[j].x > max.x)
                    max.x = geometry->morphTarget[i].verts[j].x;
                if (geometry->morphTarget[i].verts[j].y > max.y)
                    max.y = geometry->morphTarget[i].verts[j].y;
                if (geometry->morphTarget[i].verts[j].z > max.z)
                    max.z = geometry->morphTarget[i].verts[j].z;
            }
            max.x += 9999.0f;
            max.y += 9999.0f;
            max.z += 9999.0f;
            min.x += 9999.0f;
            min.y += 9999.0f;
            min.z += 9999.0f;
            float x_diff = (max.x - min.x) / 2.0f;
            float y_diff = (max.y - min.y) / 2.0f;
            float z_diff = (max.z - min.z) / 2.0f;
            geometry->morphTarget[i].boundingSphere.center.x = max.x - x_diff;
            geometry->morphTarget[i].boundingSphere.center.y = max.y - y_diff;
            geometry->morphTarget[i].boundingSphere.center.z = max.z - z_diff;
            if (x_diff > y_diff) {
                if (x_diff > z_diff)
                    geometry->morphTarget[i].boundingSphere.radius = x_diff;
                else
                    geometry->morphTarget[i].boundingSphere.radius = z_diff;
            }
            else {
                if (y_diff > z_diff)
                    geometry->morphTarget[i].boundingSphere.radius = y_diff;
                else
                    geometry->morphTarget[i].boundingSphere.radius = z_diff;
            }
        }
    }
}

// trilist
unsigned int CWCONV::mesh::get_trilist_tri_count(unsigned int num_verts) {
    return num_verts / 3;
}

void CWCONV::mesh::geometry_generate_trilist(gtaRwGeometry * geometry) {
    if (geometry->triangles)
        gtaMemFree(geometry->triangles);
    geometry->numTriangles = get_trilist_tri_count(geometry->numVertices);
    geometry->triangles = (gtaRwTriangle *)gtaMemAlloc(sizeof(gtaRwTriangle) * geometry->numTriangles);
    for (int i = 0; i < geometry->numTriangles; i++)
    {
        geometry->triangles[i].mtlId = 0;
        geometry->triangles[i].vertA = i * 3;
        geometry->triangles[i].vertB = i * 3 + 1;
        geometry->triangles[i].vertC = i * 3 + 2;
    }
}

// tristrip
void CWCONV::mesh::geometry_mesh_begin(gtaRwGeometry * geometry, unsigned int mesh_count) {
    geometry->Extension.mesh.Destroy();
    geometry->Extension.mesh.Initialise(1, mesh_count, geometry->numTriangles);
}

void CWCONV::mesh::geometry_bind_mesh(gtaRwGeometry * geometry, unsigned int mesh, unsigned int vertex_at, unsigned int vertex_count, unsigned int material) {
    geometry->Extension.mesh.meshes[mesh].Destroy();
    geometry->Extension.mesh.meshes[mesh].Initialise(vertex_count, material);
    for (int i = 0; i < vertex_count; i++)
        geometry->Extension.mesh.meshes[mesh].indices[i] = vertex_at + i;
}

void CWCONV::mesh::geometry_mesh_end(gtaRwGeometry * geometry) {
    geometry->RecalculateFaces();
}

void UncompressVector(gtaRwV3d * dest, short * src) {
    dest->x = (float)src[0] / 4096.0f;
    dest->y = (float)src[1] / 4096.0f;
    dest->z = (float)src[2] / 4096.0f;
}

void UncompressVector32(gtaRwV3d * dest, int * src) {
    dest->x = (float)src[0] / 4096.0f;
    dest->y = (float)src[1] / 4096.0f;
    dest->z = (float)src[2] / 4096.0f;
}

void UncompressVector2d(gtaRwV3d * dest, short * src) {
    dest->x = (float)src[0] / 4096.0f;
    dest->y = (float)src[1] / 4096.0f;
}

void UncompressVector2d32(gtaRwV3d * dest, int * src) {
    dest->x = (float)src[0] / 4096.0f;
    dest->y = (float)src[1] / 4096.0f;
}

void UncompressVectorLong(gtaRwV3d * dest, short * src) {
    dest->x = (float)src[0] / 64.0f;
    dest->y = (float)src[1] / 64.0f;
    dest->z = (float)src[2] / 64.0f;
}

bool DoDffExport(FILE * globalFile, char * modelName, char * outputFileName) {
    CWCONV::CTWModel model(globalFile);
    if (!model.loaded)
        return false;
    gtaRwStream *stream = gtaRwStreamOpen(rwSTREAMFILENAME, rwSTREAMWRITE, outputFileName);
    if (!stream)
        return false;
    gtaRwClump dff;

    // Init dff

    dff.numAtomics = model.numMatrices;
    dff.atomics = (gtaRwAtomic *)gtaMemAlloc(sizeof(gtaRwAtomic) * dff.numAtomics);
    for (int i = 0; i < dff.numAtomics; i++)
        dff.atomics[i].Initialise(i, i, rpATOMICRENDER, false);
    dff.geometryList.Initialise(dff.numAtomics);
    dff.frameList.Initialise(model.numMatrices);
    gtaRwV3d right = { 1.0f, 0.0f, 0.0f };
    gtaRwV3d top = { 0.0f, 1.0f, 0.0f };
    gtaRwV3d at = { 0.0f, 0.0f, 1.0f };
    gtaRwV3d posn = { 0.0f, 0.0f, 0.0f };
    dff.frameList.frames[0].Initialise(&right, &top, &at, &posn, -1, 0);
    dff.frameList.frames[0].Extension.nodeName.Initialise(modelName);

    // create nodes

    for (int i = 1; i < model.numMatrices; i++) {
        UncompressVector(&right, &model.matrices[i - 1].right_x);
        UncompressVector(&top, &model.matrices[i - 1].top_x);
        UncompressVector(&at, &model.matrices[i - 1].at_x);
        UncompressVector32(&posn, &model.matrices[i - 1].x);
        dff.frameList.frames[i].Initialise(&right, &top, &at, &posn, model.matrices[i - 1].parentNode - 1, 0);
        char nodeName[32];
        sprintf(nodeName, "node_%d", i);
        dff.frameList.frames[i].Extension.nodeName.Initialise(nodeName);
    }
    GeomInfo *ginfos = new GeomInfo[dff.geometryList.geometryCount];

    // for all geometries

    for (int i = 0; i < dff.geometryList.geometryCount; i++) {
        ginfos[i].currentMesh = 0;
        ginfos[i].currentVertex = 0;
        ginfos[i].numMaterials = 0;
        ginfos[i].numVertices = 0; // total
        ginfos[i].textured = 0;

        // find how many materials and vertices we have
        for (int j = 0; j < model.numMaterials; j++) {
            if (model.materials[j].node == i) {
                ginfos[i].numMaterials++;
                ginfos[i].numVertices += model.materials[j].vertexCount;
                if (!ginfos[i].textured) {
                    if (model.materials[j].texture != -1)
                        ginfos[i].textured = true;
                }
            }
        }
        gtaRwUInt32 geomFlags = rpGEOMETRYTRISTRIP | rpGEOMETRYPOSITIONS | rpGEOMETRYNORMALS | rpGEOMETRYMODULATEMATERIALCOLOR;
        dff.geometryList.geometries[i].Initialise(0, ginfos[i].numVertices, 1, geomFlags, 1, 0.0f, 0.0f, 0.0f, 0.0f);
        if (ginfos[i].textured)
            dff.geometryList.geometries[i].textured = true;
        dff.geometryList.geometries[i].matList.Initialise(ginfos[i].numMaterials);
        CWCONV::mesh::geometry_mesh_begin(&dff.geometryList.geometries[i], ginfos[i].numMaterials);
    }
    unsigned int totalVert = 0;

    // for all materials
    for (int mat = 0; mat < model.numMaterials; mat++) {

        //get geom id for this mat
        unsigned int id = model.materials[mat].node;

        // fill vertices
        for (int i = ginfos[id].currentVertex; i < (ginfos[id].currentVertex + model.materials[mat].vertexCount); i++) {
            UncompressVectorLong(&dff.geometryList.geometries[id].morphTarget[0].verts[i], &model.vertices[totalVert].x);
            dff.geometryList.geometries[id].morphTarget[0].normals[i].x = (float)model.vertices[totalVert].nx / 32767.0f;
            dff.geometryList.geometries[id].morphTarget[0].normals[i].y = (float)model.vertices[totalVert].ny / 32767.0f;
            dff.geometryList.geometries[id].morphTarget[0].normals[i].z = (float)model.vertices[totalVert].nz / 32767.0f;
            UncompressVectorLong(&dff.geometryList.geometries[id].morphTarget[0].verts[i], &model.vertices[totalVert].x);
            dff.geometryList.geometries[id].texCoords[0][i].u = (float)model.vertices[totalVert].u / 2048.0f;
            dff.geometryList.geometries[id].texCoords[0][i].v = (float)model.vertices[totalVert].v / 2048.0f;
            totalVert++;
        }

        // bind mesh
        CWCONV::mesh::geometry_bind_mesh(&dff.geometryList.geometries[id], ginfos[id].currentMesh,
            ginfos[id].currentVertex, model.materials[mat].vertexCount, ginfos[id].currentMesh);

        ginfos[id].currentVertex += model.materials[mat].vertexCount;

        // setup material
        dff.geometryList.geometries[id].matList.materials[ginfos[id].currentMesh].Initialise(255, 255, 255, 255, false, 1.0f, 1.0f);
        if (model.materials[mat].texture != -1) {
            dff.geometryList.geometries[id].matList.materials[ginfos[id].currentMesh].textured = true;
            char texturename[32];
            sprintf(texturename, "texture%d", model.materials[mat].texture);
            dff.geometryList.geometries[id].matList.materials[ginfos[id].currentMesh].texture.Initialise(rwFILTERLINEAR, rwTEXTUREADDRESSCLAMP,
                rwTEXTUREADDRESSCLAMP, false, texturename, NULL);
        }

        ginfos[id].currentMesh++;
    }

    // for all geometries
    for (int i = 0; i < dff.geometryList.geometryCount; i++)
        CWCONV::mesh::geometry_mesh_end(&dff.geometryList.geometries[i]);

    delete[] ginfos;

    // delete unused atomics/geometries
    CWCONV::mesh::clump_delete_empty_data(&dff);

    // Write dff
    dff.StreamWrite(stream);
    dff.Destroy();
    gtaRwStreamClose(stream);
    return true;
}
