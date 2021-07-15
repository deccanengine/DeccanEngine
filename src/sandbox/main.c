#include <deccanengine/deccan.h>
#include "player.h"

uint64_t count = 0;
deccan_timer_t timer;
deccan_camera_t camera;

void begin(deccan_scene_t *scene) {
    deccan_object_t player = deccan_object_new_object(&(deccan_object_desc_t){
        .name = "main player",
        .cb = {
            [DE_OBJECT_ATBEGINNING] = _player_begin,
            [DE_OBJECT_ATSTEP] = _player_step,
            [DE_OBJECT_ATRENDER] = _player_render,
            [DE_OBJECT_ATEND] = _player_end,
        },
    });

    deccan_scene_instantiate_object(scene, NULL, player);

    deccan_object_t none = deccan_object_new_object(&(deccan_object_desc_t){
        .name = "none",
        .cb = {
            [DE_OBJECT_ATBEGINNING] = _none_begin,
            [DE_OBJECT_ATSTEP] = _none_step,
            [DE_OBJECT_ATRENDER] = _none_render,
            [DE_OBJECT_ATEND] = _none_end,
        },
    });

    deccan_scene_instantiate_object(scene, NULL, none);

    deccan_asset_load_from_file("texture", "logo.png", "602.png", false);

    deccan_camera_init(&camera, 0.1f, 100.0f);
}

void render(deccan_scene_t *scene) {
    vec2s viewport = deccan_core_get_resolution();

    deccan_renderer_set_clear_color((vec4s){0.0f, 0.0f, 0.0f, 1.0f});

    camera.cam.position = (vec3s){0.0f, 0.0f, 1.0f};
    deccan_camera_set_viewport(&camera, viewport);
    deccan_camera_set_ortho(&camera, 30.0f);
    deccan_scene_set_camera(scene, &camera);
}

int main(int argc, char **argv) {
    DE_UNUSED(argc);
    DE_UNUSED(argv);

    bool created = deccan_app_init(&(deccan_core_desc_t){
        .title = "Test",
        .resolution = (vec2s){ 640.0f, 640.0f },
        .fullscreen = false,
        .vsync = false,
        .resizable = false,
        .close_on_escape = true,
        .fps = 120.0f,
    });

    if (created) {
        deccan_scenelayer_t *scene_mod = deccan_scenelayer_create(&(deccan_scenelayer_desc_t){
            .name = "scene_mod",
            .cb = {
                [DE_SCENE_LAYER_ATBEGINNING] = begin,
                [DE_SCENE_LAYER_ATPOSTSTEP] = render,
            },
        });

        deccan_scene_t *scene = deccan_scene_new_scene(&(deccan_scene_desc_t){
            .name = "scene0",
            .layers = { deccan_physics_layer(), scene_mod },
        });

        deccan_world_add_scene(scene, false);

        deccan_app_update();
    }

    atexit(deccan_app_quit);

    return 0;
}
