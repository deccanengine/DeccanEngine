#include "../corelib/Deccan.h"
#include "player.h"

uint64_t count = 0;
DeccanTimer timer;
DeccanSpriteAsset *text;

DeccanGameObject s;

void begin1();
void step1();
void render1();
void end1();

void color_mod(DeccanFlecsIter *it) {
    DeccanColor *color = DE_FlecsIterColumn(it, "Color", 1);
    DeccanCompState2D *state = DE_FlecsIterColumn(it, "State2D", 2);

    for(int i = 0; i < it->count; i++) {
        color[i].r += 1;
        state[i].position[1] += 1;
    }
}

void x_mod(DeccanFlecsIter *it) {
    DeccanCompState2D *state = DE_FlecsIterColumn(it, "State2D", 1);

    for(int i = 0; i < it->count; i++) {
        state[i].position[0] += 1;
    }
}

void begin() {
    /* Start here */
    DE_ComponentsRegisterAll();

    DeccanGameObject player = DE_ObjectNewObject("main player");
	DeccanObjectInfo *info = DE_ObjectGetComponent(player, "Info");
    info->AtBeginning = _player_begin;
    info->AtStep = _player_step;
    info->AtRender = _player_render;
    info->AtEnd = _player_end;
    DE_ObjectMakePrefab(player);
	DE_SceneInstantiateObject(player);

    s = DE_ObjectNewObject("Circle");
    DeccanObjectInfo *sinfo = DE_ObjectGetComponent(s, "Info");
	sinfo->AtBeginning = _none_begin;
    sinfo->AtStep = _none_step;
    sinfo->AtRender = _none_render;
    sinfo->AtEnd = _none_end;
	DE_ObjectMakePrefab(s);

    DE_AssetLoadAnimatedSprite("arrow0",
        "arrow0.png",
        "arrow1.png",
        "arrow2.png",
        "arrow3.png",
        NULL
    );
    DE_AssetLoadFont("arial", "arial.ttf");

    DE_TimerStart(&timer);

    DE_RendererSetBackgroundColor((DeccanColor){255, 255, 255, 255});

    text = DE_FontText(DE_AssetGetFont("arial"), "Hello! This is Deccan Game Engine", 0, (DeccanColor){0, 0, 0, 0});

    DE_VarNew(DE_CoreGetVarManager(), "hola", DECCAN_VARTYPE_STRING);
    DE_VarSetString(DE_CoreGetVarManager(), "hola", "test string");

    DE_FlecsRegisterComponent("Color", sizeof(DeccanColor), ECS_ALIGNOF(DeccanColor));
    DE_FlecsSystem(color_mod, "color_mod", "Color, State2D", DECCAN_ECS_TYPE_ON_UPDATE);
    DE_FlecsSystem(x_mod, "x_mod", "State2D", DECCAN_ECS_TYPE_ON_UPDATE);
}

void render();
void end();

void step() {
    /* Start here */
	if(DE_InputKeyReleased(DECCAN_KEY_P)) {
		DeccanGameScene *scene = DE_SceneNewScene("scene1");
		scene->AtFirstFrame = begin1;
		scene->AtStep = step1;
		scene->AtRender = render1;
		scene->AtEnd = end1;

		DE_SceneAddScene(scene, true);
	}
}

void render() {
    /* Start here */
    if(DE_InputKeyReleased(DECCAN_KEY_SPACE) && DE_TimerGetTime(&timer).milliseconds > 500) {
        size_t memory_needed = snprintf(NULL, 0, "circle: %I64ld", count+1) + 1;
        char *name = DE_Alloc(memory_needed, 1);
        sprintf(name, "circle%I64ld", count++);

		DeccanGameObject prefab = DE_SceneGetObject("Circle");
        DeccanGameObject object_to_push = DE_ObjectMakeCopy(prefab);
        DE_ObjectSetName(object_to_push, name);
        DE_SceneInstantiateObject(object_to_push);

        DE_TimerReset(&timer);
        DE_Free(name);
    }

	DE_SpriteBlit((vec4){100, 100, 0, 0}, 0, 0, DE_AssetGetSprite("arrow0"));
    DE_SpriteBlitScaled((vec4){10, 10, 0, 0}, (vec2){1.0f, 1.0f}, 0, 0, text);
}

void end() {
    /* Start here */
	DE_SpriteDelete(DE_AssetGetSprite("arrow0"));
	DE_FontDelete(DE_AssetGetFont("arial"));
}

void begin1() {
    DE_FlecsRegisterComponent("Color", sizeof(DeccanColor), ECS_ALIGNOF(DeccanColor));
}

void step1() {
	
}

void render1() {
	DE_DrawFilledRect((vec4){100, 100, 100, 100}, (DeccanColor){128, 128, 255, 255});
}

void end1() {

}

int main(int argc, char **argv) {
	DE_UNUSED(argc); DE_UNUSED(argv);

#if 0
	const char *text = DE_String_New("hello");
	DE_AssetLoadAsset("test", "hi", (void*)text);

	char *hi = DE_AssetGetAsset("test", "hi");
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
        DeccanGameScene *scene = DE_SceneNewScene("scene0");
        scene->AtFirstFrame = begin;
        scene->AtStep = step;
        scene->AtRender = render;
        scene->AtEnd = end;
        DE_SceneAddScene(scene, false);

        DE_AppUpdate();
    }
    atexit(DE_AppQuit);

	return 0;
}
