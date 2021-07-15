/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/world.h>
#include <deccanengine/world/flecs.h>
#include <deccanengine/world/components/transform.h>
#include <deccanengine/world/components/rigid_body.h>
#include <deccanengine/world/components/collider.h>

#include "../systems.h"
#include "../../physics/transform_sync.h"

DE_PRIV void box_collider_init(deccan_flecs_iter_t *it) {
    deccan_scene_t *scene = deccan_world_get_current_scene();

    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_rigid_body_t *rigid_body = deccan_flecs_iter_column(it, "RigidBody", 2);
    deccan_comp_box_collider_t *box_coll = deccan_flecs_iter_column(it, "BoxCollider", 3);

    for (int i = 0; i < it->count; i += 1) {
        double width = box_coll[i].width;
        double height = box_coll[i].height;
        double edge_radius = box_coll[i].edge_radius;

        double mass = cpBodyGetMass(rigid_body[i]._body);
        cpBodySetMoment(rigid_body[i]._body, cpMomentForBox(mass, width, height));

        box_coll[i]._shape = cpBoxShapeNew(rigid_body[i]._body, width, height, edge_radius);
        cpSpaceAddShape(scene->physics_space, box_coll[i]._shape);

        physics_sync_gameobject(&transform[i], &rigid_body[i]);
    }
}

DE_IMPL void system_init_colliders(void) {
    deccan_flecs_register_system(box_collider_init, "CollidersInit", "Transform, RigidBody, BoxCollider", EcsOnSet);
}
