#include "../Systems.h"
#include "../Components/RigidBody.h"
#include "../Physics.h"
#include "../../World/Flecs.h"

DE_PRIV void physics_body_init(deccan_flecs_iter_t *it) {
    deccan_comp_rigid_body_t *rigid_body = deccan_flecs_iter_column(it, "RigidBody", 1);

    for (int i = 0; i < it->count; i += 1) {
        float mass = 10, radius = 2;
        float moment = cpMomentForCircle(mass, 0, radius, cpvzero);

        rigid_body[i].body = cpSpaceAddBody(deccan_physics_get_space(), 
            cpBodyNew(mass, moment));
    }
} 

DE_IMPL void deccan_physics_system_init_physics_body(void) {
    deccan_flecs_system(physics_body_init, "PhysicsBodyInit", "RigidBody", EcsOnSet);
}

