/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "config.h"

#include "core/asset.h"
#include "core/core.h"
#include "core/input.h"
#include "core/object.h"
#include "core/scene.h"

#include "physics/shape.h"
#include "physics/collider.h"
#include "physics/collision.h"

#include "renderer/camera.h"
#include "renderer/color.h"
#include "renderer/draw.h"
#include "renderer/renderer.h"
#include "renderer/texture.h"

#include "utils/message.h"
#include "utils/timer.h"
#include "utils/vector.h"

#ifdef __STDC__
    #define NAMESPACE(x) struct DE_Module_##x {
    #define ENDNAME() };
    #define INTERFACE(t,n,...) t (*n)( __VA_ARGS__); 
    #define DECLARE(x) extern struct DE_Module_##x x
#elif __cplusplus
    #define NAMESPACE(x)
    #define INTERFACE(t,n,...) t n(__VA_ARGS__);
    #define DECLARE(x)
#else
    #error "Deccan Engine: Unsupported programming language"
#endif

NAMESPACE(Asset)
    INTERFACE(void, LoadTexture, const char *name, const char *path);
    INTERFACE(DE_Texture*, GetTexture, const char *name);
ENDNAME()

NAMESPACE(Core)
    INTERFACE(void, SetGlobalInfo, DE_GameInfo *engine);
    INTERFACE(DE_GameInfo*, GetGlobalInfo,);

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

    INTERFACE(void, SendMessage, const char *msg);
    INTERFACE(bool, ReceiveMessage, const char *msg);
ENDNAME()

NAMESPACE(Input)
    INTERFACE(DE_KeyState, GetKey, int key_code);
    INTERFACE(DE_MouseState, GetMouseButton, int button_code);
    INTERFACE(DE_Vector2i, GetMousePos,);
    INTERFACE(DE_Vector2f, GetRelativeMousePos,);
    INTERFACE(int, MouseScrollHorizontal,);
    INTERFACE(int, MouseScrollVertical,);

    INTERFACE(bool, KeyPressed, int key_code);
    INTERFACE(bool, KeyReleased, int key_code);
    INTERFACE(bool, KeyHeld, int key_code);
    INTERFACE(bool, ButtonDown, int button_code);
    INTERFACE(bool, ButtonUp, int button_code);
ENDNAME()

#define obj_func(x) void (*x)(DE_GameObject *object)

NAMESPACE(Object)
    INTERFACE(DE_GameObject*, NewObject, const char *name, const char *type, obj_func(af), obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae));
    INTERFACE(void, InstantiateObject, DE_GameObject *object);
    INTERFACE(DE_GameObject*, GetObject, const char *name);
    INTERFACE(void, GetObjectOfType, const char *name, obj_func(func));

    INTERFACE(void, SetAngle, DE_GameObject *obj, double angle);

    INTERFACE(double, GetAngle,);

    INTERFACE(void, Rotate, DE_GameObject *obj, double angle);
    INTERFACE(void, RotateTowardsObject, DE_GameObject *obj, DE_GameObject *target);
    INTERFACE(void, RotateTowardsPosition, DE_GameObject *obj, DE_Vector2f pos);
ENDNAME()

#undef obj_func

#define void_func(x) void (*x)(void)

NAMESPACE(Scene)
    INTERFACE(DE_GameScene*, NewScene, const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae));
    INTERFACE(void, AddScene, DE_GameScene *scene, bool is_replacing);
    INTERFACE(void, RemoveScene,);

    INTERFACE(DE_GameScene*, CurrentScene,);
    INTERFACE(void, PauseScene, bool pause);
    INTERFACE(bool, IsScenePaused,);
ENDNAME()

#undef void_func

NAMESPACE(Collision)
    INTERFACE(DE_Collider, NewRectCollider, DE_PosRect rect);
    INTERFACE(DE_Collider, NewCircleCollider, DE_Circle circle);

    INTERFACE(bool, TestVecVecFrom, DE_Vector2f *v1, DE_Vector2f *v2);
    INTERFACE(bool, TestRectRectFrom, DE_PosRect *r1, DE_PosRect *r2);
    INTERFACE(bool, TestCircleCircleFrom, DE_Circle *c1, DE_Circle *c2);
    INTERFACE(bool, TestVecRectFrom, DE_Vector2f *vec, DE_PosRect *rect);
    INTERFACE(bool, TestCircleVecFrom, DE_Circle *circle, DE_Vector2f *vec);
    INTERFACE(bool, TestRectCircleFrom, DE_PosRect *rect, DE_Circle *circle);
    INTERFACE(bool, TestFrom, DE_GameObject *obj1, DE_GameObject *obj2);
    INTERFACE(bool, TestVecFrom, DE_GameObject *obj, DE_Vector2f *vec);
    INTERFACE(bool, Test, const char *name1, const char *name2);
ENDNAME()

NAMESPACE(Camera)
    INTERFACE(void, Move, DE_Vector2f pos);
    INTERFACE(void, CenterOn, DE_GameObject *obj);

    INTERFACE(void, SetPosition, DE_Vector2f pos);
    INTERFACE(void, SetBounds, DE_PosRect rect);

    INTERFACE(DE_Vector2f, GetPosition,);
    INTERFACE(DE_PosRect, GetBounds,);
ENDNAME()

NAMESPACE(Renderer)
    INTERFACE(void, Clear,);
    INTERFACE(void, ClearColor, DE_Color color);

    INTERFACE(void, SetBackgroundColor, DE_Color color);
    INTERFACE(void, SetBackgroundTexture, DE_Texture *texture);
    INTERFACE(void, SetTarget, DE_Texture *target);
    INTERFACE(void, SetColor, DE_Color color);
    INTERFACE(void, SetPixelSize, DE_Vector2f size);
    INTERFACE(void, SetBlendMode, int blend_mode);

    INTERFACE(DE_Color, GetBackgroundColor,);
    INTERFACE(DE_Texture*, GetBackgroundTexture,);
    INTERFACE(DE_Texture*, GetTarget,);
    INTERFACE(DE_Color, GetColor,);
    INTERFACE(DE_Vector2f, GetPixelSize,);
    INTERFACE(DE_BlendMode, GetBlendMode,);

    INTERFACE(void, DrawPoint, DE_Vector2f pos, DE_Color color);
    INTERFACE(void, DrawLine, DE_Vector2f start, DE_Vector2f end, DE_Color color);
    INTERFACE(void, DrawRect, DE_Rect rect, DE_Color color);
    INTERFACE(void, DrawFilledRect, DE_Rect rect, DE_Color color);
    INTERFACE(void, DrawCircle, DE_Circle circle, DE_Color color);
    INTERFACE(void, DrawFilledCircle, DE_Circle circle, DE_Color color);

    INTERFACE(void, TextureSetColor, DE_Texture *texture, DE_Color color);

    INTERFACE(DE_Vector2i, TextureGetSize, DE_Texture *texture);

    INTERFACE(void, TextureBlit, DE_Rect rect, double angle, int flip, DE_Texture *texture);
    INTERFACE(void, TextureBlitScaled, DE_Rect rect, DE_Vector2f scale, double angle, int flip, DE_Texture *texture);
    INTERFACE(void, TextureBlitPartial, DE_Rect rect, DE_Rect dim, double angle, int flip, DE_Texture *texture);
ENDNAME()

NAMESPACE(Clock)
    INTERFACE(void, Delay, int32_t ms);
    INTERFACE(DE_Timer, NewTimer,);
ENDNAME()

DECLARE(Asset);
DECLARE(Core);
DECLARE(Input);
DECLARE(Object);
DECLARE(Scene);
DECLARE(Collision);
DECLARE(Camera);
DECLARE(Renderer);
DECLARE(Clock);

typedef DE_GameInfo Info;
typedef DE_GameScene GameScene;
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