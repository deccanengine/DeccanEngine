/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/components/rigid_body.h>

////////////////////////////////////////////////////////////////////////////////
// Force and Impulse
////////////////////////////////////////////////////////////////////////////////

void deccan_comp_rigid_body_apply_force_world(deccan_object_t obj, vec2s force, vec2s point) {
    deccan_comp_rigid_body_t *rb = deccan_object_get_component(obj, "RigidBody");
    if (rb) {
        cpBodyApplyForceAtWorldPoint(rb->_body, cpv(force.x, force.y), cpv(point.x, point.y));
    }
}

void deccan_comp_rigid_body_apply_force_local(deccan_object_t obj, vec2s force, vec2s point) {
    deccan_comp_rigid_body_t *rb = deccan_object_get_component(obj, "RigidBody");
    if (rb) {
        cpBodyApplyForceAtLocalPoint(rb->_body, cpv(force.x,force.y), cpv(point.x, point.y));
    }
}

void deccan_comp_rigid_body_apply_impulse_world(deccan_object_t obj, vec2s force, vec2s point) {
    deccan_comp_rigid_body_t *rb = deccan_object_get_component(obj, "RigidBody");
    if (rb) {
        cpBodyApplyImpulseAtWorldPoint(rb->_body, cpv(force.x, force.y), cpv(point.x, point.y));
    }
}

void deccan_comp_rigid_body_apply_impulse_local(deccan_object_t obj, vec2s force, vec2s point) {
    deccan_comp_rigid_body_t *rb = deccan_object_get_component(obj, "RigidBody");
    if (rb) {
        cpBodyApplyImpulseAtLocalPoint(rb->_body, cpv(force.x, force.y), cpv(point.x, point.y));
    }
}
