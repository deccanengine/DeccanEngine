#include "deccan.h"

struct DE_Asset Deccan_Asset = {
    DE_Asset_load_texture,
    DE_Asset_get_texture
};

struct DE_Core Deccan_Core = {
    DE_Core_set_global_engine, 
    DE_Core_get_global_engine,
    
    DE_Core_init,
    DE_Core_quit,
    DE_Core_run,
    
    DE_Core_set_title,
    DE_Core_set_mode,
    DE_Core_set_fullscreen,
    DE_Core_set_vsync_status,
    DE_Core_set_framerate_limit,

    DE_Core_get_title,
    DE_Core_get_mode,
    DE_Core_get_fullscreen_status,
    DE_Core_get_vsync_status,
    DE_Core_get_framerate_limit,
    DE_Core_get_average_framerate
};

struct DE_Input Deccan_Input = {
    DE_Input_get_key, 
    DE_Input_get_mouse_button, 
    DE_Input_get_mouse_pos,
    DE_Input_get_relative_mouse_pos,
    DE_Input_mouse_scroll_horizontal,
    DE_Input_mouse_scroll_vertical,

    DE_Input_key_pressed,
    DE_Input_key_released,
    DE_Input_key_held,
    DE_Input_button_down,
    DE_Input_button_up
};

struct DE_Object Deccan_Object = { 
    DE_Object_new_object,
    DE_Object_instantiate_object,
    DE_Object_get_object,
    DE_Object_get_object_of_type
};

struct DE_Scenes Deccan_Scenes = {
    DE_Scenes_new_scene,
    DE_Scenes_add_scene,
    DE_Scenes_remove_scene,
    DE_Scenes_current_scene,
    DE_Scenes_pause_scene,
    DE_Scenes_is_scene_paused
};

struct DE_Collision Deccan_Collision = { 
    DE_Collision_new_rect_collider,
    DE_Collision_new_circle_collider,

    DE_Collision_test_vec_vec_from,
    DE_Collision_test_rect_rect_from,
    DE_Collision_test_circle_circle_from,
    DE_Collision_test_vec_rect_from,
    DE_Collision_test_circle_vec_from,
    DE_Collision_test_rect_circle_from,
    DE_Collision_test_from,
    DE_Collision_test_vec_from,
    DE_Collision_test
};

struct DE_Camera Deccan_Camera = {
    DE_Camera_move,
    DE_Camera_set_position,
    DE_Camera_center_on
};

struct DE_Renderer Deccan_Renderer = {
    DE_Renderer_clear,

    DE_Renderer_set_color,
    DE_Renderer_set_pixel_size,

    DE_Renderer_get_color,
    DE_Renderer_get_pixel_size,

    DE_Renderer_draw_point,
    DE_Renderer_draw_line,
    DE_Renderer_draw_rect,
    DE_Renderer_draw_filled_rect,
    DE_Renderer_draw_circle,
    DE_Renderer_draw_filled_circle,

    DE_Renderer_texture_set_color,
    DE_Renderer_texture_draw,
    DE_Renderer_texture_draw_with_scale
};

struct DE_Clock Deccan_Clock = {
    DE_Clock_delay,
    DE_Clock_new_timer
};