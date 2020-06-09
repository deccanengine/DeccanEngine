#pragma once
#include "../../Config.h"
#include "../Object.h"
#include "../ECSystem.h"

typedef struct State2D {
    Vector3f position;
    Vector2f scale;
    double   rotation;

    bool is_z_dirty;
} State2D;

void State2D_InitInternal();

State2D *State2D_Init();

void State2D_SetZOrder(GameObject *obj, int32_t z);