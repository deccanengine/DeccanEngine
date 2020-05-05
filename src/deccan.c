#include "deccan.h"

struct DE_Module_Asset Asset = {
    DE_Asset_LoadTexture,
    DE_Asset_GetTexture
};

struct DE_Module_Core Core = {
    DE_Core_SetGlobalInfo, 
    DE_Core_GetGlobalInfo,
    
    DE_Core_Init,
    DE_Core_Quit,
    DE_Core_Run,
    
    DE_Core_SetTitle,
    DE_Core_SetMode,
    DE_Core_SetFullscreen,
    DE_Core_SetVsyncStatus,
    DE_Core_SetFramerateLimit,

    DE_Core_GetTitle,
    DE_Core_GetMode,
    DE_Core_GetFullscreenStatus,
    DE_Core_GetVsyncStatus,
    DE_Core_GetFramerateLimit,
    DE_Core_GetAverageFramerate,

    DE_Core_SendMessage,
    DE_Core_ReceiveMessage
};

struct DE_Module_Input Input = {
    DE_Input_GetKey, 
    DE_Input_GetMouseButton, 
    DE_Input_GetMousePos,
    DE_Input_GetRelativeMousePos,
    DE_Input_MouseScrollHorizontal,
    DE_Input_MouseScrollVertical,

    DE_Input_KeyPressed,
    DE_Input_KeyReleased,
    DE_Input_KeyHeld,
    DE_Input_ButtonDown,
    DE_Input_ButtonUp
};

struct DE_Module_Object Object = { 
    DE_Object_NewObject,
    DE_Object_InstantiateObject,
    DE_Object_GetObject,
    DE_Object_GetObjectOfType
};

struct DE_Module_Scene Scene = {
    DE_Scene_NewScene,
    DE_Scene_AddScene,
    DE_Scene_RemoveScene,
    DE_Scene_CurrentScene,
    DE_Scene_PauseScene,
    DE_Scene_IsScenePaused
};

struct DE_Module_Collision Collision = { 
    DE_Collision_NewRectCollider,
    DE_Collision_NewCircleCollider,

    DE_Collision_VecVec,
    DE_Collision_RectRect,
    DE_Collision_CircleCircle,
    DE_Collision_VecRect,
    DE_Collision_CircleVec,
    DE_Collision_RectCircle,
    DE_Collision_ObjectObject,
    DE_Collision_ObjectVec,
    DE_Collision_Test
};

struct DE_Module_Camera Camera = {
    DE_Camera_Move,
    DE_Camera_CenterOn,

    DE_Camera_SetPosition,
    DE_Camera_SetBounds,

    DE_Camera_GetPosition,
    DE_Camera_GetBounds
};

struct DE_Module_Renderer Renderer = {
    DE_Renderer_Clear,
    DE_Renderer_ClearColor,

    DE_Renderer_SetBackgroundColor,
    DE_Renderer_SetBackgroundTexture,
    DE_Renderer_SetTarget,
    DE_Renderer_SetColor,
    DE_Renderer_SetPixelSize,
    DE_Renderer_SetBlendMode,

    DE_Renderer_GetTarget,
    DE_Renderer_GetColor,
    DE_Renderer_GetPixelSize,
    DE_Renderer_GetBlendMode,

    DE_Renderer_DrawPoint,
    DE_Renderer_DrawLine,
    DE_Renderer_DrawRect,
    DE_Renderer_DrawFilledRect,
    DE_Renderer_DrawCircle,
    DE_Renderer_DrawFilledCircle,

    DE_Renderer_TextureSetColor,

    DE_Renderer_TextureGetSize,

    DE_Renderer_TextureBlit,
    //DE_Renderer_TextureBlitSized,
    DE_Renderer_TextureBlitScaled,
    DE_Renderer_TextureBlitPartial
};

struct DE_Module_Clock Clock = {
    DE_Clock_Delay,
    DE_Clock_NewTimer
};