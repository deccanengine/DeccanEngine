#define DECCAN_SHORT_NAMES
#include <Deccan/Deccan.h>
#include "player.h"

Timer timer;
TextureAsset *text;

void begin() {
    /* Start here */
    GameObject *player = Object_NewObject("main player", "player");
    player->order.z = 10;
    player->AtBeginning = _player_begin;
    player->AtStep = _player_step;
    player->AtRender = _player_render;
    player->AtEnd = _player_end;
    Object_InstantiateObject(player);
    
    Asset_LoadTexture("arrow0", "arrow0.png");
    Asset_LoadTexture("arrow0", "arrow1.png");
    Asset_LoadTexture("arrow0", "arrow2.png");
    Asset_LoadTexture("arrow0", "arrow3.png");
    Asset_LoadFont("arial", "arial.ttf");

    Clock_StartTimer(&timer);

    Renderer_SetBackgroundColor(ColorList_White);

    text = Font_Text(Asset_GetFont("arial"), "Hello! This is Deccan Game Engine", 0, ColorList_Black);
}

void step() {
    /* Start here */
}

void render() {
    /* Start here */
    if(Input_KeyReleased(KeyCode_Space) && Clock_GetTime(&timer).milliseconds > 200) {
        GameObject *s = Object_NewObject("circle", "static");
        s->position.x = Object_GetObject("main player")->position.x + 10;
        s->position.y = Object_GetObject("main player")->position.y + 10;
        s->AtBeginning = _none_begin;
        s->AtStep = _none_step;
        s->AtRender = _none_render;
        s->AtEnd = _none_end;
        Object_InstantiateObject(s);
        
        Clock_ResetTimer(&timer);
    }
    
    if(Input_KeyReleased(KeyCode_Up)) {
        Vector2f size = Renderer_GetPixelSize();
        size.x += 0.1f;
        size.y += 0.1f; 
        Renderer_SetPixelSize(size);
    }
    else if(Input_KeyReleased(KeyCode_Down)) {
        Vector2f size = Renderer_GetPixelSize();
        size.x -= size.x ? 0.1f : 0.0f; 
        size.y -= size.y ? 0.1f : 0.0f;
        Renderer_SetPixelSize(size);
    }

    if(Input_KeyReleased(KeyCode_Left)) {
        Vector2i mode = Core_GetMode();
        mode.x += 40;
        mode.y += 40; 
        Core_SetMode(mode);
    }
    else if(Input_KeyReleased(KeyCode_Right)) {
        Vector2i mode = Core_GetMode();
        mode.x -= mode.x > 40 ? 40 : 0;
        mode.y -= mode.y > 40 ? 40 : 0; 
        Core_SetMode(mode);
    }
    
    if(Input_KeyReleased(KeyCode_V)) {
        Core_SetVsyncStatus(false);
    }

    if(Input_KeyReleased(KeyCode_L)) {
        bool is = Texture_GetAnimLoop(Asset_GetTexture("arrow0"));
        Texture_SetAnimLoop(Asset_GetTexture("arrow0"), is ? false : true); // It toogles 

        Object_SetZOrder(Object_GetObject("main player"), 20);
    }

    if(Input_KeyReleased(KeyCode_X)) {
        Object_DeleteObject(Object_GetObject("main player"));
    }

    Texture_BlitScaled((Rect){10, 10, 0, 0}, (Vector2f){1.0f, 1.0f}, 0, 0, text);
}

void end() {
    /* Start here */
}

int main(int argc, char **argv) {
    if(Core_Init("Test", (Vector2i){640, 320})) {
        Scene_AddScene(Scene_NewScene("scene0", begin, step, render, end), false);
        Core_Run(120.0f);
    }
    atexit(Core_Quit);
}