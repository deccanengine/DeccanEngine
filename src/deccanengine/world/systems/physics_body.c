/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/flecs.h>
#include <deccanengine/world/world.h>
#include <deccanengine/world/components/transform.h>
#include <deccanengine/world/components/rigid_body.h>
#include <deccanengine/physics/physics.h>

#include "../systems.h"
#include "../../physics/transform_sync.h"

cpBodyType get_body_type(deccan_rigid_body_type_t type) {
    switch (type) {
        case DECCAN_RIGID_BODY_KINEMATIC: return CP_BODY_TYPE_KINEMATIC;
        case DECCAN_RIGID_BODY_STATIC: return CP_BODY_TYPE_STATIC;
        default: return CP_BODY_TYPE_DYNAMIC;
    }

    return -1; // unreachable
}

DE_PRIV void physics_body_init(deccan_flecs_iter_t *it) {
    deccan_scene_t *scene = deccan_world_get_current_scene();

    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_rigid_body_t *rigid_body = deccan_flecs_iter_column(it, "RigidBody", 2);

    for (int i = 0; i < it->count; i += 1) {
        double mass = rigid_body[i].mass;
        double moment = rigid_body[i].moment;

        rigid_body[i]._body = cpSpaceAddBody(scene->physics_space, cpBodyNew(mass, moment));

        deccan_rigid_body_type_t type = rigid_body[i].type;
        cpBodySetType(rigid_body[i]._body, type);
        cpBodySetUserData(rigid_body[i]._body, &(deccan_object_t){ it->entities[i] });

        physics_sync_physicsbody(&transform[i], &rigid_body[i]);
    }
}

DE_IMPL void system_init_physics_body(void) {
    deccan_flecs_register_system(physics_body_init, "PhysicsBodyInit", "Transform, RigidBody", EcsOnSet);
}
