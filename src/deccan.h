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
    #define NAMESPACE(x) struct DE_##x
    #define INTERFACE(t,n,...) t (*n)( __VA_ARGS__); 
    #define DECLARE(x) extern struct DE_##x Deccan_##x
#elif __cplusplus
    #define NAMESPACE(x) namespace Deccan::##x
    #define INTERFACE(t,n,...) t n(__VA_ARGS__);
    #define DECLARE(x)
#else
    #error "Deccan Engine: Unsupported programming language"
#endif

NAMESPACE(Asset) {
    INTERFACE(void, LoadTexture, const char *name, const char *path);
    INTERFACE(DE_Texture*, GetTexture, const char *name);
};

NAMESPACE(Core) {
    INTERFACE(void, SetGlobalEngine, DE_Info *engine);
    INTERFACE(DE_Info*, GetGlobalEngine,);

    INTERFACE(int , Init, const char *title, DE_Vector2i mode);
    INTERFACE(void, Quit, void);
    INTERFACE(void, Run, float fps);

    INTERFACE(void, SetTitle, const char *name);
    INTERFACE(void, SetMode, DE_Vector2i mode);
    INTERFACE(void, SetFullscreen, void);
    INTERFACE(void, SetVsyncStatus, bool vsync);
    INTERFACE(void, SetFramerateLimit, float fps);

    INTERFACE(const char*, GetTitle,);
    INTERFACE(DE_Vector2i, GetMode,);
    INTERFACE(bool, GetFullscreenStatus,);
    INTERFACE(bool, GetVsyncStatus,);
    INTERFACE(float, GetFramerateLimit,);
    INTERFACE(float, GetAverageFramerate,);
};

NAMESPACE(Input) {
    INTERFACE(DE_KeyState, GetKey, int key_code);
    INTERFACE(DE_MouseState, GetMouseButton, int button_code);
    INTERFACE(DE_Vector2i, GetMousePos,);
    INTERFACE(DE_Vector2i, GetRelativeMousePos,);
    INTERFACE(int, MouseScrollHorizontal,);
    INTERFACE(int, MouseScrollVertical,);

    INTERFACE(bool, KeyPressed, int key_code);
    INTERFACE(bool, KeyReleased, int key_code);
    INTERFACE(bool, KeyHeld, int key_code);
    INTERFACE(bool, ButtonDown, int button_code);
    INTERFACE(bool, ButtonUp, int button_code);
};

#define obj_func(x) void (*x)(DE_GameObject *object)

NAMESPACE(Object) {
    INTERFACE(DE_GameObject*, NewObject, const char *name, const char *type, obj_func(af), obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae));
    INTERFACE(void, InstantiateObject, DE_GameObject *object);
    INTERFACE(DE_GameObject*, GetObject, const char *name);
    INTERFACE(void, GetObjectOfType, const char *name, obj_func(func));
};

#undef obj_func

#define void_func(x) void (*x)(void)

NAMESPACE(Scenes) {
    INTERFACE(DE_Scene*, NewScene, const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae));
    INTERFACE(void, AddScene, DE_Scene *scene, bool is_replacing);
    INTERFACE(void, RemoveScene,);

    INTERFACE(DE_Scene*, CurrentScene,);
    INTERFACE(void, PauseScene, bool pause);
    INTERFACE(bool, IsScenePaused,);
};

#undef void_func

NAMESPACE(Collision) {
    INTERFACE(DE_Collider, NewRectCollider, DE_PosRect rect);
    INTERFACE(DE_Collider, NewCircleCollider, DE_Circle circle);

    INTERFACE(bool, TestVecVecFrom, DE_Vector2i *v1, DE_Vector2i *v2);
    INTERFACE(bool, TestRectRectFrom, DE_PosRect *r1, DE_PosRect *r2);
    INTERFACE(bool, TestCircleCircleFrom, DE_Circle *c1, DE_Circle *c2);
    INTERFACE(bool, TestVecRectFrom, DE_Vector2i *vec, DE_PosRect *rect);
    INTERFACE(bool, TestCircleVecFrom, DE_Circle *circle, DE_Vector2i *vec);
    INTERFACE(bool, TestRectCircleFrom, DE_PosRect *rect, DE_Circle *circle);
    INTERFACE(bool, TestFrom, DE_GameObject *obj1, DE_GameObject *obj2);
    INTERFACE(bool, TestVecFrom, DE_GameObject *obj, DE_Vector2i *vec);
    INTERFACE(bool, Test, const char *name1, const char *name2);
};

NAMESPACE(Camera) {
    INTERFACE(void, Move, DE_Vector2i pos);
    INTERFACE(void, SetPosition, DE_Vector2i pos);
    INTERFACE(void, CenterOn, DE_GameObject *obj);
};

NAMESPACE(Renderer) {
    INTERFACE(void, Clear, DE_Color color);

    INTERFACE(void, SetColor, DE_Color color);
    INTERFACE(void, SetPixelSize, DE_Vector2f size);

    INTERFACE(DE_Color, GetColor,);
    INTERFACE(DE_Vector2f, GetPixelSize,);

    INTERFACE(void, DrawPoint, DE_Vector2i pos, DE_Color color);
    INTERFACE(void, DrawLine, DE_Vector2i start, DE_Vector2i end, DE_Color color);
    INTERFACE(void, DrawRect, DE_Rect rect, DE_Color color);
    INTERFACE(void, DrawFilledRect, DE_Rect rect, DE_Color color);
    INTERFACE(void, DrawCircle, DE_Circle circle, DE_Color color);
    INTERFACE(void, DrawFilledCircle, DE_Circle circle, DE_Color color);

    INTERFACE(void, TextureSetColor, DE_Texture *texture, DE_Color color);
    INTERFACE(void, TextureDraw, DE_Vector2i pos, SDL_Texture *texture);
    INTERFACE(void, TextureDrawWithScale, DE_Vector2i pos, DE_Vector2f scale, SDL_Texture *texture);
};

NAMESPACE(Clock) {
    INTERFACE(void, Delay, int32_t ms);
    INTERFACE(DE_Timer, NewTimer,);
};

DECLARE(Asset);
DECLARE(Core);
DECLARE(Input);
DECLARE(Object);
DECLARE(Scenes);
DECLARE(Collision);
DECLARE(Camera);
DECLARE(Renderer);
DECLARE(Clock);

#ifdef __STDC__
    #ifdef DECCAN_SHORT_NAMES
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
    #endif
#endif