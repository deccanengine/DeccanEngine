#include "State2D.h"
#include "../Scene.h"

void AtStep0(GameObject *obj);

void State2D_InitInternal() {
    ECSystem_RegisterComponent("State2D");
}

State2D *State2D_Init() {
    State2D *state = DE_NEW(State2D, 1);
    state->position.x = 0;
    state->position.y = 0;
    state->position.z = 0;
    state->scale.x    = 1;
    state->scale.y    = 1;
    state->rotation   = 0;
    state->is_z_dirty = true;

    return state;
}