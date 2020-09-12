#include "../corelib/Deccan.h"
#include "player.h"

Timer timer;
SpriteAsset *text;

void begin() {
    /* Start here */
    GameObject *player = Object_NewObject("main player");
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

    DE_Var_New(DE_Core_GetVarManager(), "hola", DECCAN_VARTYPE_STRING);
    DE_Var_SetString(DE_Core_GetVarManager(), "hola", "test string");

    State2D_Register();
    Collider_Register();

    GameScene *scene = Scene_CurrentScene();
    ecs_entity_t FLECS__EColor = ecs_new_component(scene->world, 0, "Color", sizeof(Color), ECS_ALIGNOF(Color));
}

void step() {
    /* Start here */
}

void render() {
    /* Start here */

    if(Input_KeyReleased(KeyCode_Space) && Clock_GetTime(&timer).milliseconds > 200) {
        GameObject *s = Object_NewObject("circle");
        s->AtBeginning = _none_begin;
        s->AtStep = _none_step;
        s->AtRender = _none_render;
        s->AtEnd = _none_end;

        Object_InstantiateObject(s);

        Clock_ResetTimer(&timer);
    }

	Sprite_Blit((vec4){100, 100, 0, 0}, 0, 0, Asset_GetSprite("arrow0"));

    Sprite_BlitScaled((vec4){10, 10, 0, 0}, (vec2){1.0f, 1.0f}, 0, 0, text);
}

void end() {
    /* Start here */
	Sprite_Delete(Asset_GetSprite("arrow0"));
	Font_Delete(Asset_GetFont("arial"));
}

int main(int argc, char **argv) {
	DE_UNUSED(argc); DE_UNUSED(argv);

#if 0
	const char *text = DE_String_New("hello");
	DE_Asset_LoadAsset("test", "hi", (void*)text);

	char *hi = DE_Asset_GetAsset("test", "hi");
	printf("text after: %s\n", hi);
#endif

    DeccanSettings settings = {0};
    settings.title = "Test";
    settings.resolution[0] = settings.resolution[1] = 640.0f;
	settings.fullscreen = false;
	settings.vsync = false;		// Probably not working in some environments, report
	settings.resizable = false;
	settings.closeOnEscape = true;
    settings.fps = 120.0f;

    if(DE_App_Init(&settings)) {
        GameScene *scene = Scene_NewScene("scene0");
        scene->AtFirstFrame = begin;
        scene->AtStep = step;
        scene->AtRender = render;
        scene->AtEnd = end;
        Scene_AddScene(scene, false);

        DE_App_Update();
    }
    atexit(DE_App_Quit);

	return 0;
}
