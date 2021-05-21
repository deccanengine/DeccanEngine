#include "../Systems.h"
#include "../Components/RigidBody.h"
#include "../Physics.h"
#include "../../World/Flecs.h"
#include "../../World/Components/Transform.h"

DE_PRIV void physics_sim_init(deccan_flecs_iter_t *it) {
    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_rigid_body_t *rigid_body = deccan_flecs_iter_column(it, "RigidBody", 2);

    for (int i = 0; i < it->count; i += 1) {
        cpVect position = cpBodyGetPosition(rigid_body[i].body);
        transform[i].position.x = position.x;
        transform[i].position.y = position.y;
    }
} 

DE_IMPL void deccan_physics_system_init_physics_sim(void) {
    deccan_flecs_system(physics_sim_init, "PhysicsSimulation", "Transform, RigidBody", EcsOnUpdate);
}

