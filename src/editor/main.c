#include <corelib/Deccan.h>
#include "Viewport.h"

int main(int argc, char **argv) {
    DE_UNUSED(argc);
    DE_UNUSED(argv);
    
    deccan_asset_manager_t manager = deccan_make_default_asset_manager();
    deccan_asset_set_manager_inst(&manager);

    deccan_settings_t settings = {0};
    settings.title = "Deccan Engine Editor";
    settings.resolution = (vec2s){ 1280.0f, 960.0f };
    settings.fullscreen = false;
    settings.vsync = false; 
    settings.resizable = false;
    settings.close_on_escape = true;
    settings.fps = 120.0f;

    if (deccan_app_init(&settings)) {
        deccan_game_scene_t *scene = deccan_scene_new_scene("editor");
        deccan_module_t *viewport_mod = get_viewport_module();
        deccan_scene_push_module(scene, deccan_imgui_module());
        deccan_scene_push_module(scene, viewport_mod);
        deccan_scene_add_scene(scene, false);

        deccan_app_update();
    }

    deccan_asset_destroy_manager(&manager);

    atexit(deccan_app_quit);

    return 0;
}
