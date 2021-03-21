#ifndef THINGS_H_
#define THINGS_H_

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
static int nthings = 0;

static Mesh *cubemesh;
static Mesh *ellipmesh;
static Mesh *surfrevmesh;
static Mesh *flatmesh;

void
thingsinit()
{

    cubemesh = memalloc(sizeof(Mesh));
    loadmesh(cubemesh, "../assets/models/cube.model");

    ellipmesh = memalloc(sizeof(Mesh));
    loadmesh(ellipmesh, "../assets/models/ellipsoid.model");

    surfrevmesh = memalloc(sizeof(Mesh));
    loadmesh(surfrevmesh, "../assets/models/surfrev.model");

    flatmesh = memalloc(sizeof(Mesh));
    loadmesh(flatmesh, "../assets/models/heightmap.model");

    // // TODO: temporary
    // Model *cube = memalloc(sizeof(Model));
    // modelinit(cube, cubemesh);
    // setposmodel(cube, 0.0f, 2.0f, 0.0f);
    // // setrotmodel(cube, 45.0f, 0.0f, 0.0f);
    // cube->scale = 0.5f;

    // Model *ellip = memalloc(sizeof(Model));
    // modelinit(ellip, ellipmesh);
    // setposmodel(ellip, 2.0f, 2.0f, 0.0f);
    // // setrotmodel(ellip, 45.0f, 0.0f, 0.0f);
    // ellip->scale = 1.0f;

    // Model *surf = memalloc(sizeof(Model));
    // modelinit(surf, surfrevmesh);
    // setposmodel(surf, -2.0f, 2.0f, 0.0f);
    // // setrotmodel(surf, 45.0f, 0.0f, 0.0f);
    // surf->scale = 0.1f;

    Model *flat = memalloc(sizeof(Model));
    modelinit(flat, flatmesh);
    setposmodel(flat, 0.0f, 0.0f, 0.0f);
    flat->scale = 0.1f;

    allthings = memalloc(sizeof(Thing) * 1);
    allthings->model = flat;
    allthings->next = NULL;
    // allthings->model = cube;
    // allthings->next = (allthings + 1);
    // (allthings + 1)->model = ellip;
    // (allthings + 1)->next = (allthings + 2);
    // (allthings + 2)->model = surf;
    // (allthings + 2)->next = (allthings + 3);
    // (allthings + 3)->model = flat;
    // (allthings + 3)->next = NULL;

    nthings += 1;
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
    
    memfree(cubemesh);
    memfree(ellipmesh);
    memfree(surfrevmesh);
    memfree(flatmesh);
    memfree(allthings);
}

#endif