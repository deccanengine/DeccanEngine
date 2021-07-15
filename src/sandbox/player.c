#include "player.h"

bool selected = false;
vec2 offset;

void _player_begin(deccan_object_t this) {
    deccan_object_set_component(this, "Collider", &(deccan_comp_collider_t){
        .type = DECCAN_COLLIDER_RECT,
        .rect = { .x = -5, .y = -5, .z = 10.0f, .w = 10.0f }
        // .rect = { .x = -0.5f, .y = -0.5f, .z = 1.0f, .w = 1.0f }
    });

    deccan_object_set_component(this, "Transform", &(deccan_comp_transform_t){
        .position = { .x = 0.0f, .y = 0.0f, .z = 0.0f },
        .scale = { .x = 5.0f, .y = 5.0f, .z = 1.0f },
        .rotation = { .z = 0.0f },
    });

    deccan_object_set_component(this, "DrawableSprite", &(deccan_comp_drawable_sprite_t){
        .texture = deccan_asset_get_raw(deccan_asset_get("texture", "logo.png")),
        .material = (deccan_material_t){
            .color = (deccan_color_t){ 255, 255, 255, 255 },
        },
    });

    deccan_comp_transform_t *transform = deccan_object_get_component(this, "Transform");

    float width = 5;

    deccan_object_set_component(this, "RigidBody", &(deccan_comp_rigid_body_t){
        .mass = 10,
    });

    deccan_object_set_component(this, "BoxCollider", &(deccan_comp_box_collider_t){
        .width = width,
        .height = width,
    });
}

void _player_step(deccan_object_t this) {
    static float force = 10;
    deccan_comp_transform_t *transform = deccan_object_get_component(this, "Transform");
    deccan_comp_rigid_body_t *rigidbody = deccan_object_get_component(this, "RigidBody");

    if (deccan_input_key_held(DECCAN_KEY_W)) {
        deccan_comp_rigid_body_apply_impulse_local(this, (vec2s){0, force}, (vec2s){0, 0});
    }
    else if (deccan_input_key_held(DECCAN_KEY_S)) {
        deccan_comp_rigid_body_apply_impulse_local(this, (vec2s){0, -force}, (vec2s){0, 0});
    }
    else if (deccan_input_key_held(DECCAN_KEY_A)) {
        deccan_comp_rigid_body_apply_impulse_local(this, (vec2s){-force, 0}, (vec2s){0, 0});
    }
    else if (deccan_input_key_held(DECCAN_KEY_D)) {
        deccan_comp_rigid_body_apply_impulse_local(this, (vec2s){force, 0}, (vec2s){0, 0});
    }

    if (deccan_input_key_released(DECCAN_KEY_O)) {
        force -= 1;
    }
    else if (deccan_input_key_released(DECCAN_KEY_P)) {
        force += 1;
    }

    /* Center the camera on player */
    // Camera_CenterOn(this);

    deccan_camera_t *camera = deccan_scene_get_camera(deccan_world_get_current_scene());
    vec2s pos1 = deccan_input_get_mouse_pos();
    vec3s pos = deccan_camera_convert_screen_to_world(camera, (vec3s){pos1.x, pos1.y, 0.0f});

    // NOTE: currently this doesn't work when zoom != 0
    if (deccan_comp_collider_check_object_with_vector(this, pos.raw)) {
        if (deccan_input_button_down(DECCAN_BUTTON_LEFT)) {
            selected = true;
            offset[0] = pos.x - transform->position.x;
            offset[1] = pos.y - transform->position.y;
        }
        else if (deccan_input_button_up(DECCAN_BUTTON_LEFT)) {
            selected = false;
        }
    }

    if (selected) {
        transform->position.x = pos.x - offset[0];
        transform->position.y = pos.y - offset[1];
    }
}

void _player_render(deccan_object_t this) {
    deccan_comp_transform_t *transform = deccan_object_get_component(this, "Transform");
}

void _player_end(deccan_object_t this) {
    DE_UNUSED(this);
}

void _none_begin(deccan_object_t this) {
    deccan_object_set_tag(this, "isEnemy");

    deccan_object_set_component(this, "Transform", &(deccan_comp_transform_t){
        .position = { .x = 11.0f, .y = 0.0f, .z = 0.0f },
        .scale = { .x = 10.0f, .y = 10.0f, .z = 1.0f },
        .rotation = { .z = 0.0f },
    });

    deccan_object_set_component(this, "DrawableSprite", &(deccan_comp_drawable_sprite_t){
        .texture = deccan_asset_get_raw(deccan_asset_get("texture", "logo.png")),
        .material = (deccan_material_t){
            .color = (deccan_color_t){ 255, 255, 255, 255 },
        },
    });

    float width = 10;

    deccan_object_set_component(this, "RigidBody", &(deccan_comp_rigid_body_t){
        .mass = 10,
    });

    deccan_object_set_component(this, "BoxCollider", &(deccan_comp_box_collider_t){
        .width = width,
        .height = width,
    });
}

void _none_step(deccan_object_t this) {
    DE_UNUSED(this);
}

void _none_render(deccan_object_t this) {
    DE_UNUSED(this);
}

void _none_end(deccan_object_t this) {
    DE_UNUSED(this);
}
