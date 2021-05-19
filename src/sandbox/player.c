#include "player.h"

bool selected = false;
vec2 offset;

void _player_begin(deccan_game_object_t this) {
    deccan_object_info_t *info = deccan_object_get_component(this, "Info");

    deccan_object_set_component(this, "Collider", &(deccan_comp_collider_t){
        .type = DECCAN_COLLIDER_RECT, 
        .rect = { .x = 0, .y = 0, .z = 50, .w = 50 }
    });

    deccan_object_set_component(this, "Transform", &(deccan_comp_transform_t){
        .position = { .x = 1.0f, .y = 0.0f, .z = 0.0f },
        .scale = { .x = 5.0f, .y = 5.0f, .z = 1.0f },
        .rotation = { .z = DE_PI/3 },
    });

    deccan_object_set_component(this, "DrawableSprite", &(deccan_comp_drawable_sprite_t){
        .texture = deccan_asset_get_raw(deccan_asset_get("texture", "logo.png")),
        .material = (deccan_material_t){
            .color = (deccan_color_t){ 255, 255, 255, 255 },
        },
    });
}

void _player_step(deccan_game_object_t this) {
    static float SpeedModifier = 2e-2f;
    deccan_comp_transform_t *state = deccan_object_get_component(this, "Transform");

    if (deccan_input_key_held(DECCAN_KEY_W)) {
        state->position.y += SpeedModifier;
    }
    else if (deccan_input_key_held(DECCAN_KEY_S)) {
        state->position.y -= SpeedModifier;
    }
    else if (deccan_input_key_held(DECCAN_KEY_A)) {
        state->position.x -= SpeedModifier;
    }
    else if (deccan_input_key_held(DECCAN_KEY_D)) {
        state->position.x += SpeedModifier;
    }

    if (deccan_input_key_released(DECCAN_KEY_O)) {
        SpeedModifier -= 1;
    }
    else if (deccan_input_key_released(DECCAN_KEY_P)) {
        SpeedModifier += 1;
    }

    /* Center the camera on player */
    // Camera_CenterOn(this);
    
    vec2s pos = deccan_input_get_mouse_pos();
    if (deccan_comp_collider_check_object_with_vector(this, pos.raw)) {
        if (deccan_input_button_down(DECCAN_BUTTON_LEFT)) {
            selected = true;
            offset[0] = pos.x - state->position.x;
            offset[1] = pos.y - state->position.y;
        }
        else if (deccan_input_button_up(DECCAN_BUTTON_LEFT)) {
            selected = false;
        }
    }

    if (selected) {
        state->position.x = pos.x - offset[0];
        state->position.y = pos.y - offset[1];
    }
}

void _player_render(deccan_game_object_t this) {
    deccan_comp_transform_t *state = deccan_object_get_component(this, "Transform");

    igBegin("Transform", NULL, 0);
    igDragFloat("X", &state->position.x, 0.1f, 0.0f, 0.0f, "%.2f", 0);
    igDragFloat("Y", &state->position.y, 0.1f, 0.0f, 0.0f, "%.2f", 0);
    igDragFloat("Z", &state->position.z, 0.1f, 0.0f, 0.0f, "%.2f", 0);
    igEnd();
}

void _player_end(deccan_game_object_t this) {
    DE_UNUSED(this);
}

void _none_begin(deccan_game_object_t this) {
    deccan_game_object_t player = deccan_scene_get_object("main player");
    deccan_comp_transform_t *statePlayer = deccan_object_get_component(player, "Transform");

    deccan_object_set_component(this, "Transform", &(deccan_comp_transform_t){
        .position = { .x = statePlayer->position.x, .y = statePlayer->position.y }
    });
    deccan_object_set_component(this, "Collider", &(deccan_comp_collider_t){
        .type = DECCAN_COLLIDER_RECT, 
        .rect = { .x = 0, .y = 0, .z = 40, .w = 40}
    });
    deccan_object_set_tag(this, "isEnemy");
}

void _none_step(deccan_game_object_t this) {
    DE_UNUSED(this);
}

void _none_render(deccan_game_object_t this) {
    deccan_comp_transform_t *state = deccan_object_get_component(this, "Transform");
}

void _none_end(deccan_game_object_t this) {
    DE_UNUSED(this);
}
