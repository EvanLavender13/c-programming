#ifndef THINGS_H_
#define THINGS_H_

#include <gen.h>
#include <mem.h>
#include <mesh.h>
#include <model.h>

typedef struct Thing Thing;
struct Thing
{
    Model *model;
    Thing *next;
    Thing *prev;
};

static Thing *allthings = NULL;
// static Thing *head;
// static Thing *tail;
static int nthings = 0;

static Mesh *blockmesh;
static Mesh *colormesh;
static Mesh *objmesh;

// cube vertices
float v[] = {
    -0.5f,  0.5f,  0.5f, // V0
    -0.5f, -0.5f,  0.5f, // V1
     0.5f, -0.5f,  0.5f, // V2
     0.5f,  0.5f,  0.5f, // V3
    -0.5f,  0.5f, -0.5f, // V4
     0.5f,  0.5f, -0.5f, // V5
    -0.5f, -0.5f, -0.5f, // V6
     0.5f, -0.5f, -0.5f, // V7
    
    // For text coords in top face
    -0.5f, 0.5f, -0.5f, // V8: V4 repeated
     0.5f, 0.5f, -0.5f, // V9: V5 repeated
    -0.5f, 0.5f,  0.5f, // V10: V0 repeated
     0.5f, 0.5f,  0.5f, // V11: V3 repeated

    // For text coords in right face
    0.5f,  0.5f, 0.5f, // V12: V3 repeated
    0.5f, -0.5f, 0.5f, // V13: V2 repeated

    // For text coords in left face
    -0.5f,  0.5f, 0.5f, // V14: V0 repeated
    -0.5f, -0.5f, 0.5f, // V15: V1 repeated

    // For text coords in bottom face
    -0.5f, -0.5f, -0.5f, // V16: V6 repeated
     0.5f, -0.5f, -0.5f, // V17: V7 repeated
    -0.5f, -0.5f,  0.5f, // V18: V1 repeated
     0.5f, -0.5f,  0.5f  // V19: V2 repeated
};

int i[] = {
    0, 1, 3, 3, 1, 2,       // Front face
    8, 10, 11, 9, 8, 11,    // Top Face
    12, 13, 7, 5, 12, 7,    // Right face
    14, 15, 6, 4, 14, 6,    // Left face
    16, 18, 19, 17, 16, 19, // Bottom face
    4, 6, 7, 5, 4, 7        // Back face
};

// float c[] = {
//     0.5f, 0.0f, 0.0f,
//     0.0f, 0.5f, 0.0f,
//     0.0f, 0.0f, 0.5f,
//     0.0f, 0.5f, 0.5f,
//     0.5f, 0.0f, 0.0f,
//     0.0f, 0.5f, 0.0f,
//     0.0f, 0.0f, 0.5f,
//     0.0f, 0.5f, 0.5f,
// };

float t[] = {
    0.0f, 0.0f,
    0.0f, 0.5f,
    0.5f, 0.5f,
    0.5f, 0.0f,

    0.0f, 0.0f,
    0.5f, 0.0f,
    0.0f, 0.5f,
    0.5f, 0.5f,
    // For text coords in top face
    0.0f, 0.5f,
    0.5f, 0.5f,
    0.0f, 1.0f,
    0.5f, 1.0f,
    // For text coords in right face
    0.0f, 0.0f,
    0.0f, 0.5f,
    // For text coords in left face
    0.5f, 0.0f,
    0.5f, 0.5f,
    // For text coords in bottom face
    0.5f, 0.0f,
    1.0f, 0.0f,
    0.5f, 0.5f,
    1.0f, 0.5f
};

void
thingsinit()
{
    int texid;
    MeshDef tdef;
    MeshDef cdef;

    texid = texinit("../textures/grassblock.png");
    // define mesh
    // TODO: this structure is already annoying
    tdef.vertices = v;
    tdef.nvertices = sizeof(v) / sizeof(float);
    tdef.vsize = sizeof(float) * tdef.nvertices;
    tdef.indices = i;
    tdef.nindices = sizeof(i) / sizeof(int);
    tdef.isize = sizeof(int) * tdef.nindices;
    tdef.texid = texid;
    tdef.texcoords = t;
    tdef.ntexcoords = sizeof(t) / sizeof(float);
    tdef.tsize = sizeof(float) * tdef.ntexcoords;

    cdef.vertices = v;
    cdef.nvertices = sizeof(v) / sizeof(float);
    cdef.vsize = sizeof(float) * cdef.nvertices;
    cdef.indices = i;
    cdef.nindices = sizeof(i) / sizeof(int);
    cdef.isize = sizeof(int) * cdef.nindices;
    //tdef.texid = texid;
    cdef.texcoords = t;
    cdef.ntexcoords = sizeof(t) / sizeof(float);
    cdef.tsize = sizeof(float) * cdef.ntexcoords;

    blockmesh = memalloc(sizeof(*blockmesh));
    meshinit(blockmesh, &tdef);

    colormesh = memalloc(sizeof(*colormesh));
    meshinit(colormesh, &cdef);

    objmesh = memalloc(sizeof(Mesh));
    // meshinitobj(objmesh, "../models/cube.obj");
    // objmesh->texid = texid;

    // TODO: temporary
    Model *block1 = memalloc(sizeof(Model));
    modelinit(block1, blockmesh);
    setposmodel(block1, 0.0f, 0.0f, -2.0f);
    block1->scale = 0.2f;

    Model *block2 = memalloc(sizeof(Model));
    modelinit(block2, blockmesh);
    setposmodel(block2, 0.5f, 0.5f, -2.0f);
    block2->scale = 0.5f;

    Model *block3 = memalloc(sizeof(Model));
    modelinit(block3, colormesh);
    setposmodel(block3, 0.0f, 0.0f, -2.5f);
    block3->scale = 0.5f;

    Model *block4 = memalloc(sizeof(Model));
    modelinit(block4, colormesh);
    setposmodel(block4, 0.5f, 0.0f, -2.5f);
    block4->scale = 0.5f;

    allthings = memalloc(sizeof(Thing) * 4);
    allthings->model = block1;
    allthings->next = (allthings + 1);
    (allthings + 1)->model = block2;
    (allthings + 1)->next = (allthings + 2);
    (allthings + 2)->model = block3;
    (allthings + 2)->next = (allthings + 3);
    (allthings + 3)->model = block4;
    (allthings + 3)->next = NULL;

    nthings += 4;

    // generate stuff
    gencube();
}

void
delthing(Thing *t)
{
    delmodel(t->model);
    nthings--;
}

void
delthings()
{
    Thing *head;
    Thing *temp;

    head = allthings;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delthing(temp);
    }

    memfree(allthings);
    delmesh(blockmesh);
    delmesh(colormesh);
    delmesh(objmesh);
}

#endif