#define DECCAN_SHORT_NAMES
#include "../corelib/Deccan.h"
#include "player.h"

Timer timer;
SpriteAsset *text;
	
void begin() {
    /* Start here */
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

    Renderer_SetBackgroundColor((Color){255, 255, 255, 255});

    text = Font_Text(Asset_GetFont("arial"), "Hello! This is Deccan Game Engine", 0, (Color){0, 0, 0, 0});
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
	
	Sprite_Blit((Rect){100, 100, 0, 0}, 0, 0, Asset_GetSprite("arrow0"));

    Sprite_BlitScaled((Rect){10, 10, 0, 0}, (Vector2){1.0f, 1.0f}, 0, 0, text);
}

void end() {
    /* Start here */
	Sprite_Delete(Asset_GetSprite("arrow0"));
	Font_Delete(Asset_GetFont("arial"));
}

int main(int argc, char **argv) {
	DE_UNUSED(argc); DE_UNUSED(argv);
	
    /* Register all the components */
    ECSystem_RegisterComponent("NULL");

    State2D_Register();
    Collider_Register();

    // To do: material component
    ECSystem_RegisterComponent("Color");

    CoreSettings settings = {0};
    settings.title = "Test";
    settings.resolution = (Vector2){640, 640};
	settings.fullscreen = false;
	settings.vsync = false;		// Probably not working in some environments, report
	settings.resizable = false;
	settings.closeOnEscape = true;
    settings.fps = 120.0f;
    
    if(Core_Init(&settings)) {
        GameScene *scene = Scene_NewScene("scene0");
        scene->AtFirstFrame = begin;
        scene->AtStep = step;
        scene->AtRender = render;
        scene->AtEnd = end;
        Scene_AddScene(scene, false);
        
        Core_Run();
    }
    atexit(Core_Quit);
	
	return 0;
}