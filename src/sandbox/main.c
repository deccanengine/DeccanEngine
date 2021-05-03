#include <corelib/Deccan.h>
#include "player.h"

uint64_t count = 0;
deccan_timer_t timer;
deccan_camera_t camera;

void begin() {
    /* Start here */

    // TODO: Introduce hooks and callbacks here
    deccan_components_register_all();
    deccan_systems_register_all();

    deccan_game_object_t player = deccan_object_new_object("main player");
    deccan_object_info_t *info = deccan_object_get_component(player, "Info");
    info->at_beginning = _player_begin;
    info->at_step = _player_step;
    info->at_render = _player_render;
    info->at_end = _player_end;
    deccan_object_make_prefab(player);
    deccan_scene_instantiate_object(player);

    deccan_asset_load_from_file("texture", "logo.png", "602.png", false);

    deccan_camera_init(&camera, 0.1f, 100.0f);
}

void step() {
    /* Start here */
}

void render() {
    /* Start here */
    vec2s viewport;
    deccan_core_get_resolution(viewport.raw);

    deccan_renderer_set_clear_color((vec4s){0.0f, 0.0f, 0.0f, 1.0f});

    camera.cam.position = (vec3s){0.0f, 0.0f, 1.0f};
    deccan_camera_set_viewport(&camera, viewport);
    deccan_camera_set_ortho(&camera, 3.0f);

    deccan_scene_set_camera(&camera);

    igBegin("Main Window", NULL, 0);
    igText("Hello, World!");
    igEnd();
}

void end() {
    /* Start here */
}

int main(int argc, char **argv) {
    DE_UNUSED(argc);
    DE_UNUSED(argv);
    
    deccan_asset_manager_t *manager = deccan_make_default_asset_manager();
    deccan_asset_set_manager_inst(manager);

    deccan_settings_t settings = {0};
    settings.title = "Test";
    settings.resolution[0] = settings.resolution[1] = 640.0f;
    settings.fullscreen = false;
    settings.vsync = false; // Probably not working in some environments, report
    settings.resizable = false;
    settings.close_on_escape = true;
    settings.fps = 120.0f;

    if (deccan_app_init(&settings)) {
        deccan_game_scene_t *scene = deccan_scene_new_scene("scene0");
        deccan_module_t *scene_mod = deccan_module_create("scene_mod");
        scene_mod->at_beginning = begin;
        scene_mod->at_step = step;
        scene_mod->at_post_step = render;
        scene_mod->at_end = end;

        deccan_scene_push_module(scene, deccan_imgui_module());
        deccan_scene_push_module(scene, scene_mod);
        deccan_scene_add_scene(scene, false);

        deccan_app_update();
    }

    deccan_asset_destroy_manager(manager);
    deccan_free(manager);

    atexit(deccan_app_quit);

    return 0;
}
