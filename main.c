#define DECCAN_SHORT_NAMES
#include "src/deccan.h"
#include "player.h"

void begin() {
    /* Start here */
    //Asset.load_texture("arrow", "arrow0.png");
    Object.instantiate_object(Object.new_object("circle", "static", _none_begin, _none_step, _none_render, _none_end));
    Object.instantiate_object(Object.new_object("not circle", "static", _none_begin2, _none_step, _none_render, _none_end));
    Object.instantiate_object(Object.new_object("main player", "player", _player_begin, _player_step, _player_render, _player_end));
}

void step() {
    /* Start here */
}

void render() {
    Renderer.clear(ColorList.white);

    /* Start here */
}

void end() {
    /* Start here */
}

int main(int argc, char **argv) {
    if(Core.init("Test", 640, 320)) {
        Scenes.add_scene(Scenes.new_scene("scene0", begin, step, render, end), false);
        Core.run(120.0f);
    }
    atexit(Core.quit);
}