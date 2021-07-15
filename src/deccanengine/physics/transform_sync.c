/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "transform_sync.h"

void physics_sync_gameobject(deccan_comp_transform_t *transform, deccan_comp_rigid_body_t *rigid_body) {
    cpVect position = cpBodyGetPosition(rigid_body->_body);

    transform->position.x = position.x;
    transform->position.y = position.y;

    cpFloat rotation = cpBodyGetAngle(rigid_body->_body);
    transform->rotation.z = rotation;
}

void physics_sync_physicsbody(deccan_comp_transform_t *transform, deccan_comp_rigid_body_t *rigid_body) {
    cpVect position;
    position.x = transform->position.x;
    position.y = transform->position.y;
    cpBodySetPosition(rigid_body->_body, position);

    cpFloat rotation = transform->rotation.z;
    cpBodySetAngle(rigid_body->_body, rotation);
}

void physics_sync_gameobject_it(deccan_flecs_iter_t *it) {
    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_rigid_body_t *rigid_body = deccan_flecs_iter_column(it, "RigidBody", 2);

    for (int i = 0; i < it->count; i += 1) {
        physics_sync_gameobject(&transform[i], &rigid_body[i]);
    }
}


void physics_sync_physicsbody_it(deccan_flecs_iter_t *it) {
    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_rigid_body_t *rigid_body = deccan_flecs_iter_column(it, "RigidBody", 2);

    for (int i = 0; i < it->count; i += 1) {
        physics_sync_physicsbody(&transform[i], &rigid_body[i]);
    }
}
