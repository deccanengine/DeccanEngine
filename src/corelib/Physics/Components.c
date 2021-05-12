#include "Components.h"
#include "../World/Flecs.h"

DE_IMPL void deccan_physics_components_register_all(void) {
    deccan_flecs_register_component("RigidBody", 
        sizeof(deccan_comp_rigid_body_t), 
        ECS_ALIGNOF(deccan_comp_rigid_body_t));
}
