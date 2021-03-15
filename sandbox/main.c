#include <corelib/Deccan.h>
#include "player.h"
#include "Texture.h"

uint64_t count = 0;
DeccanTimer timer;
DeccanCamera camera;

simgui_desc_t imgui_context = {0};

void begin() {
    /* Start here */
    DE_ImguiInit();

    // TODO: Introduce hooks and callbacks here
    DE_ComponentsRegisterAll();

    DeccanGameObject player = DE_ObjectNewObject("main player");
    DeccanObjectInfo *info = DE_ObjectGetComponent(player, "Info");
    info->AtBeginning = _player_begin;
    info->AtStep = _player_step;
    info->AtRender = _player_render;
    info->AtEnd = _player_end;
    DE_ObjectMakePrefab(player);
    DE_SceneInstantiateObject(player);

    DE_FlecsRegisterComponent("Color", sizeof(DeccanColor), ECS_ALIGNOF(DeccanColor));

    DE_CameraInit(&camera, 0.1f, 100.0f);
}

void step() {
    /* Start here */
}

void render() {
    /* Start here */
    vec2s viewport;
    DE_CoreGetResolution(viewport.raw);

    DE_RendererSetClearColor((vec4s){0.0f, 0.0f, 0.0f, 1.0f});

    camera.cam.position = (vec3s){0.0f, 0.0f, 1.0f};
    DE_CameraSetViewport(&camera, viewport);
    DE_CameraSetOrtho(&camera, 1.0f);

    DE_SceneSetCamera(&camera);

    DE_ImguiBeginRender();

    igBegin("Main Window", NULL, 0);
    igText("Hello, World!");
    igEnd();

    DE_ImguiEndRender();
}

void end() {
    /* Start here */
    DE_ImguiQuit();
}

int main(int argc, char **argv) {
    DE_UNUSED(argc);
    DE_UNUSED(argv);

    DeccanAssetManager manager;
    DE_AssetInitManager(&manager, 0, NULL);
    DE_AssetSetManagerInst(&manager);

    DeccanSettings settings = {0};
    settings.title = "Test";
    settings.resolution[0] = settings.resolution[1] = 640.0f;
    settings.fullscreen = false;
    settings.vsync = false; // Probably not working in some environments, report
    settings.resizable = false;
    settings.closeOnEscape = true;
    settings.fps = 120.0f;

    if (DE_AppInit(&settings)) {
        DeccanGameScene *scene = DE_SceneNewScene("scene0");
        scene->AtFirstFrame = begin;
        scene->AtStep = step;
        scene->AtRender = render;
        scene->AtEnd = end;
        DE_SceneAddScene(scene, false);

        DE_AppUpdate();
    }

    DE_AssetDestroyManager(&manager);

    atexit(DE_AppQuit);

    return 0;
}
