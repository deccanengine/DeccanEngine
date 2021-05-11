#include "Viewport.h"

deccan_camera_t camera;

void viewport_begin(void) {
    deccan_components_register_all();
    deccan_systems_register_all();

    deccan_camera_init(&camera, 0.1f, 100.0f);
}

void viewport_step(void) {
}

void viewport_render(void) {
    vec2s viewport = deccan_core_get_resolution();

    deccan_renderer_set_clear_color((vec4s){0.1f, 0.1f, 0.1f, 1.0f});

    camera.cam.position = (vec3s){0.0f, 0.0f, 1.0f};
    deccan_camera_set_viewport(&camera, viewport);
    deccan_camera_set_ortho(&camera, 3.0f);

    deccan_scene_set_camera(&camera);

    igBegin("Main Window", NULL, 0);
    igText("Hello, World!");
    igEnd();

}

void viewport_end(void) {
}

deccan_module_t *get_viewport_module(void) {
    deccan_module_t *viewport_mod = deccan_module_create("viewport");
    viewport_mod->at_beginning = viewport_begin;
    viewport_mod->at_step = viewport_step;
    viewport_mod->at_post_step = viewport_render;
    viewport_mod->at_end = viewport_end;
    return viewport_mod;
}
