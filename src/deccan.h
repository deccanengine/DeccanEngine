/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "config.h"

#include "core/core.h"
#include "core/input.h"
#include "core/asset.h"
#include "core/scene.h"
#include "core/object.h"

#include "renderer/renderer.h"
#include "renderer/draw.h"
#include "renderer/color.h"
#include "renderer/camera.h"
#include "renderer/texture.h"

#include "physics/shape.h"
#include "physics/collider.h"
#include "physics/collision.h"

#include "utils/timer.h"
#include "utils/vector.h"

#ifdef __STDC__
    typedef struct DE_Asset {
        void (*load_texture)(const char *name, const char *path);
        DE_Texture* (*get_texture)(const char *name);
    } DE_Asset;

    static DE_Asset Deccan_Asset = {
        DE_Asset_load_texture,
        DE_Asset_get_texture
    };

    typedef struct DE_Core {
        void (*set_global_engine)(DE_Info *engine);
        DE_Info* (*get_global_engine)();

        int  (*init)(const char *title, DE_Vector2i mode);
        void (*quit)();
        void (*run)(float fps);

        void (*set_title)(const char *name);
        void (*set_mode)(DE_Vector2i mode);
        void (*set_fullscreen)();
        void (*set_vsync_status)(bool vsync);
        void (*set_framerate_limit)(float fps);

        const char *(*get_title)();
        DE_Vector2i (*get_mode)();
        bool  (*get_fullscreen_status)();
        bool  (*get_vsync_status)();
        float (*get_framerate_limit)();
        float (*get_average_framerate)();
    } DE_Core;

    static DE_Core Deccan_Core = {
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

    typedef struct DE_Input {
        DE_KeyState (*get_key)(int key_code);
        DE_MouseState (*get_mouse_button)(int button_code);
        DE_Vector2i (*get_mouse_pos)();
        DE_Vector2i (*get_relative_mouse_pos)();
        int (*mouse_scroll_horizontal)();
        int (*mouse_scroll_vertical)();

        bool (*key_pressed)(int key_code);
        bool (*key_released)(int key_code);
        bool (*key_held)(int key_code);
        bool (*button_down)(int button_code);
        bool (*button_up)(int button_code);
    } DE_Input;

    static DE_Input Deccan_Input = {
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

    #define obj_func(x) void (*x)(DE_GameObject *object)

    typedef struct DE_Object {
        DE_GameObject *(*new_object)(const char *name, const char *type, obj_func(af), obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae));
        void (*instantiate_object)(DE_GameObject *object);
        DE_GameObject *(*get_object)(const char *name);
        void (*get_object_of_type)(const char *name, void(*func)(DE_GameObject *obj));
    } DE_Object;

    static DE_Object Deccan_Object = { 
        DE_Object_new_object,
        DE_Object_instantiate_object,
        DE_Object_get_object,
        DE_Object_get_object_of_type
    };

    #undef obj_func

    #define void_func(x) void (*x)(void)

    typedef struct DE_Scenes {
        DE_Scene *(*new_scene)(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae));
        void (*add_scene)(DE_Scene *scene, bool is_replacing);
        void (*remove_scene)();

        DE_Scene *(*current_scene)();
        void (*pause_scene)(bool pause);
        bool (*is_scene_paused)();
    } DE_Scenes;

    static DE_Scenes Deccan_Scenes = {
        DE_Scenes_new_scene,
        DE_Scenes_add_scene,
        DE_Scenes_remove_scene,
        DE_Scenes_current_scene,
        DE_Scenes_pause_scene,
        DE_Scenes_is_scene_paused
    };

    #undef void_func

    typedef struct DE_Collision {
        DE_Collider (*new_rect_collider)(DE_PosRect rect);
        DE_Collider (*new_circle_collider)(DE_Circle circle);
        
        bool (*test_vec_vec_from)(DE_Vector2i *v1, DE_Vector2i *v2);
        bool (*test_rect_rect_from)(DE_PosRect *r1, DE_PosRect *r2);
        bool (*test_circle_circle_from)(DE_Circle *c1, DE_Circle *c2);
        bool (*test_vec_rect_from)(DE_Vector2i *vec, DE_PosRect *rect);
        bool (*test_circle_vec_from)(DE_Circle *circle, DE_Vector2i *vec);
        bool (*test_rect_circle_from)(DE_PosRect *rect, DE_Circle *circle);
        bool (*test_from)(DE_GameObject *obj1, DE_GameObject *obj2);
        bool (*test_vec_from)(DE_GameObject *obj, DE_Vector2i *vec);
        bool (*test)(const char *name1, const char *name2);
    } DE_Collision;

    static DE_Collision Deccan_Collision = { 
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

    typedef struct DE_Camera {
        void (*move)(DE_Vector2i pos);
        void (*set_position)(DE_Vector2i pos);
        void (*center_on)(DE_GameObject *obj);
    } DE_Camera;

    static DE_Camera Deccan_Camera = {
        DE_Camera_move,
        DE_Camera_set_position,
        DE_Camera_center_on
    };

    typedef struct DE_Renderer {
        void (*clear)(DE_Color color);

        void (*set_color)(DE_Color color);
        void (*set_pixel_size)(DE_Vector2f size);

        DE_Color (*get_color)();
        DE_Vector2f (*get_pixel_size)();

        void (*draw_point)(DE_Vector2i pos, DE_Color color);
        void (*draw_line)(DE_Vector2i start, DE_Vector2i end, DE_Color color);
        void (*draw_rect)(DE_Rect rect, DE_Color color);
        void (*draw_filled_rect)(DE_Rect rect, DE_Color color);
        void (*draw_circle)(DE_Circle circle, DE_Color color);
        void (*draw_filled_circle)(DE_Circle circle, DE_Color color);

        void (*texture_set_color)(DE_Texture *texture, DE_Color color);
        void (*texture_draw)(DE_Vector2i pos, SDL_Texture *texture);
        void (*texture_draw_with_scale)(DE_Vector2i pos, DE_Vector2f scale, SDL_Texture *texture);
    } DE_Renderer;

    static DE_Renderer Deccan_Renderer = {
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

    typedef struct DE_Clock {
        void (*delay)(int32_t ms);
        DE_Timer (*new_timer)();
    } DE_Clock;

    static DE_Clock Deccan_Clock = {
        DE_Clock_delay,
        DE_Clock_new_timer
    };

    typedef DE_Info Info;
    typedef DE_Scene Scene;
    typedef DE_GameObject GameObject;
    typedef DE_KeyState KeyState;
    typedef DE_MouseState MouseState;
        
    typedef DE_Color Color;

    typedef DE_Collider Collider;
    typedef DE_Rect Rect;
    typedef DE_PosRect PosRect;
    typedef DE_Circle Circle;

    typedef DE_Timer Timer;
    typedef DE_Vector2i Vector2i;
    typedef DE_Vector2u Vector2u;
    typedef DE_Vector2f Vector2f;
    typedef DE_Vector3i Vector3i;

    #define Core Deccan_Core
    #define Scenes Deccan_Scenes
    #define Object Deccan_Object
    #define Input Deccan_Input
    #define Key DE_Key
    #define Button DE_Button
    #define Asset Deccan_Asset

    #define Renderer Deccan_Renderer
    #define ColorList DE_ColorList
    #define Camera Deccan_Camera

    #define Collision Deccan_Collision

    #define Clock Deccan_Clock
#elif __cplusplus

#endif