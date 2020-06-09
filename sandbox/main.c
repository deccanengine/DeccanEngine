#define DECCAN_SHORT_NAMES
#include "../corelib/Deccan.h"
#include "player.h"

Timer timer;
SpriteAsset *text;

void begin() {
    /* Start here */
    
    /* Register all the components */
    ECSystem_RegisterComponent("NULL");

    State2D_InitInternal();

    ECSystem_RegisterComponent("Color");
    ECSystem_RegisterComponent("Scale");
    ECSystem_RegisterComponent("Rotation");
    ECSystem_RegisterComponent("Collider");
    ECSystem_RegisterComponent("SpeedModifier");
    ECSystem_RegisterComponent("Position");
    ECSystem_RegisterComponent("Velocity");

    GameObject *player = Object_NewObject("main player", "player");
    player->order.z = 5;
    player->AtBeginning = _player_begin;
    player->AtStep = _player_step;
    player->AtRender = _player_render;
    player->AtEnd = _player_end;
    Object_InstantiateObject(player);
    
    Asset_LoadAnimatedSprite("arrow0", 
        "arrow0.png", 
        "arrow1.png", 
        "arrow2.png", 
        "arrow3.png", 
        NULL
    );
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
        s->AtBeginning = _none_begin;
        s->AtStep = _none_step;
        s->AtRender = _none_render;
        s->AtEnd = _none_end;

        Object_InstantiateObject(s);

        Clock_ResetTimer(&timer);
    }

    Sprite_BlitScaled((Rect){10, 10, 0, 0}, (Vector2f){1.0f, 1.0f}, 0, 0, text);
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