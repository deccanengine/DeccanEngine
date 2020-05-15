#define DECCAN_SHORT_NAMES
#include <Deccan/Deccan.h>
#include "player.h"

Timer timer;
TextureAsset *text;

void begin() {
    /* Start here */
    Object_InstantiateObject(Object_NewObject("main player", "player", NULL_OBJFUNC, _player_begin, _player_step, _player_render, _player_end));
    
    Asset_LoadTexture("arrow0", "arrow0.png");
    Asset_LoadTexture("arrow0", "arrow1.png");
    Asset_LoadTexture("arrow0", "arrow2.png");
    Asset_LoadTexture("arrow0", "arrow3.png");
    Asset_LoadFont("arial", "arial.ttf");

    Clock_StartTimer(&timer);

    Renderer_SetBackgroundColor(ColorList.white);

    text = Font_Text(Asset_GetFont("arial"), "hello", ColorList.black);
}

void step() {
    /* Start here */
}

void render() {
    /* Start here */
    if(Input_KeyReleased(Key.space) && Clock_GetTime(&timer).milliseconds > 200) {
        GameObject *s = Object_NewObject("circle", "static", NULL_OBJFUNC, _none_begin, _none_step, _none_render, _none_end);
        s->position.x = Object_GetObject("main player")->position.x + 10;
        s->position.y = Object_GetObject("main player")->position.y + 10;
        Object_InstantiateObject(s);
        
        Clock_ResetTimer(&timer);
    }
    
    if(Input_KeyReleased(Key.up)) {
        Vector2f size = Renderer_GetPixelSize();
        size.x += 0.1f;
        size.y += 0.1f; 
        Renderer_SetPixelSize(size);
    }
    else if(Input_KeyReleased(Key.down)) {
        Vector2f size = Renderer_GetPixelSize();
        size.x -= size.x ? 0.1f : 0.0f; 
        size.y -= size.y ? 0.1f : 0.0f;
        Renderer_SetPixelSize(size);
    }

    if(Input_KeyReleased(Key.left)) {
        Vector2i mode = Core_GetMode();
        mode.x += 40;
        mode.y += 40; 
        Core_SetMode(mode);
    }
    else if(Input_KeyReleased(Key.right)) {
        Vector2i mode = Core_GetMode();
        mode.x -= mode.x > 40 ? 40 : 0;
        mode.y -= mode.y > 40 ? 40 : 0; 
        Core_SetMode(mode);
    }
    
    if(Input_KeyReleased(Key.v)) {
        Core_SetVsyncStatus(false);
    }

    if(Input_KeyReleased(Key.l)) {
        bool is = Texture_GetAnimLoop(Asset_GetTexture("arrow0"));
        Texture_SetAnimLoop(Asset_GetTexture("arrow0"), is ? false : true); // It toogles 
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