#include "Physics.h"
#include "../Core/Core.h"

DE_PRIV struct {
    cpSpace *space;
} physics_info = {0};

DE_IMPL void deccan_physics_init(void) {
    cpVect gravity = cpv(0, -9.6);
    physics_info.space = cpSpaceNew();
    cpSpaceSetGravity(physics_info.space, gravity);
}

DE_IMPL void deccan_physics_quit(void) {
    cpSpaceFree(physics_info.space);
}

DE_IMPL void deccan_physics_step(void) {
    cpSpaceStep(physics_info.space, 0.00666666666666f); //deccan_core_get_delta_time());
}

DE_IMPL cpSpace *deccan_physics_get_space(void) {
    return physics_info.space;
}

DE_IMPL deccan_module_t *deccan_physics_module(void) {
    deccan_module_t *physics = deccan_module_create("physics");
    physics->at_beginning = deccan_physics_init;
    physics->at_step = deccan_physics_step;
    physics->at_end = deccan_physics_quit;
    return physics;
}
