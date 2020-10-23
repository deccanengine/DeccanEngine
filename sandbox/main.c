#include "../corelib/Deccan.h"
#include "player.h"

uint64_t count;
DeccanTimer timer;
DeccanSpriteAsset *text;

GameObject *s;

void color_mod(DeccanSysIter *it) {
    DeccanColor *color = DE_Flecs_IterColumn(it, "Color", 1);
    DeccanCompState2D *state = DE_Flecs_IterColumn(it, "State2D", 2);

    for(int i = 0; i < it->count; i++) {
        color[i].r += 1;
        state[i].position[1] += 1;
    }
}

void x_mod(DeccanSysIter *it) {
    DeccanCompState2D *state = DE_Flecs_IterColumn(it, "State2D", 1);

    for(int i = 0; i < it->count; i++) {
        state[i].position[0] += 1;
    }
}

void begin() {
    /* Start here */
    DE_Components_RegisterAll();

    GameObject *player = Object_NewObject("main player");
//     player->order.z = 5;
    player->AtBeginning = _player_begin;
    player->AtStep = _player_step;
    player->AtRender = _player_render;
    player->AtEnd = _player_end;
    Scene_InstantiateObject(player);

    s = Object_NewObject("Circle");
    s->AtBeginning = _none_begin;
    s->AtStep = _none_step;
    s->AtRender = _none_render;
    s->AtEnd = _none_end;

    DE_AssetLoadAnimatedSprite("arrow0",
        "arrow0.png",
        "arrow1.png",
        "arrow2.png",
        "arrow3.png",
        NULL
    );
    DE_AssetLoadFont("arial", "arial.ttf");

    DE_TimerStart(&timer);

    Renderer_SetBackgroundColor((DeccanColor){255, 255, 255, 255});

    text = DE_FontText(DE_AssetGetFont("arial"), "Hello! This is Deccan Game Engine", 0, (DeccanColor){0, 0, 0, 0});

    DE_VarNew(DE_Core_GetVarManager(), "hola", DECCAN_VARTYPE_STRING);
    DE_VarSetString(DE_Core_GetVarManager(), "hola", "test string");

    DE_Flecs_RegisterComponent("Color", sizeof(DeccanColor), ECS_ALIGNOF(DeccanColor));
    DE_Flecs_System(color_mod, "color_mod", "Color, State2D", DECCAN_ECS_TYPE_ON_UPDATE);
    DE_Flecs_System(x_mod, "x_mod", "State2D", DECCAN_ECS_TYPE_ON_UPDATE);
}

void step() {
    /* Start here */
}

void render() {
    /* Start here */
    if(Input_KeyReleased(KeyCode_Space) && DE_TimerGetTime(&timer).milliseconds > 2000) {
        size_t memory_needed = snprintf(NULL, 0, "circle: %I64ld", count++) + 1;
        char *name = DE_Mem_New(memory_needed, 1);
        sprintf(name, "circle%I64ld", count++);

        GameObject *object_to_push = Object_MakeCopy(s);
        Object_SetName(object_to_push, name);
        Scene_InstantiateObject(object_to_push);

        DE_TimerReset(&timer);
        DE_Mem_Delete(name);
    }

	DE_SpriteBlit((vec4){100, 100, 0, 0}, 0, 0, DE_AssetGetSprite("arrow0"));

    DE_SpriteBlitScaled((vec4){10, 10, 0, 0}, (vec2){1.0f, 1.0f}, 0, 0, text);
}

void end() {
    /* Start here */
	DE_SpriteDelete(DE_AssetGetSprite("arrow0"));
	DE_FontDelete(DE_AssetGetFont("arial"));
}

int main(int argc, char **argv) {
	DE_UNUSED(argc); DE_UNUSED(argv);

#if 0
	const char *text = DE_String_New("hello");
	DE_DE_AssetLoadAsset("test", "hi", (void*)text);

	char *hi = DE_DE_AssetGetAsset("test", "hi");
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

    if(DE_AppInit(&settings)) {
        GameScene *scene = Scene_NewScene("scene0");
        scene->AtFirstFrame = begin;
        scene->AtStep = step;
        scene->AtRender = render;
        scene->AtEnd = end;
        Scene_AddScene(scene, false);

        DE_AppUpdate();
    }
    atexit(DE_AppQuit);

	return 0;
}
