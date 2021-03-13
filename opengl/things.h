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

void
thingsinit()
{

    cubemesh = memalloc(sizeof(Mesh));
    loadmesh(cubemesh, "../assets/models/cube.model");

    ellipmesh = memalloc(sizeof(Mesh));
    loadmesh(ellipmesh, "../assets/models/ellipsoid.model");

    surfrevmesh = memalloc(sizeof(Mesh));
    loadmesh(surfrevmesh, "../assets/models/surfrev.model");

    // TODO: temporary
    Model *cube = memalloc(sizeof(Model));
    modelinit(cube, cubemesh);
    setposmodel(cube, 2.0f, 0.0f, 0.0f);
    cube->scale = 0.5f;

    Model *ellip = memalloc(sizeof(Model));
    modelinit(ellip, ellipmesh);
    setposmodel(ellip, -2.5f, 0.0f, 0.0f);
    ellip->scale = 1.0f;

    Model *surf = memalloc(sizeof(Model));
    modelinit(surf, surfrevmesh);
    setrotmodel(surf, 90.0f, 0.0f, 0.0f);
    setposmodel(surf, 0.0f, -1.0f, 0.0f);
    surf->scale = 0.1f;

    allthings = memalloc(sizeof(Thing) * 3);
    allthings->model = cube;
    allthings->next = (allthings + 1);
    (allthings + 1)-> model = ellip;
    (allthings + 1)-> next = (allthings + 2);
    (allthings + 2)-> model = surf;
    (allthings + 2)-> next = NULL;

    nthings += 3;
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
    memfree(allthings);
}

#endif