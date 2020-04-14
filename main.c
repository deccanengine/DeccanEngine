#define using_namespace_Deccan
#include "src/deccan.h"
#include "player.h"

void begin() {
    /* Start here */
    Asset.load_texture("arrow", "arrow0.png");
    Object.instantiate_object(Object.new_object("main player", "player", _player_begin, _player_step, _player_end));
}

void step() {
    Renderer.clear(ColorList.white);

    /* Start here */
    //player.at_step(&player);
}

void end() {
    /* Start here */
}

int main(int argc, char **argv) {
    if(Core.init("Test", 640, 320)) {
        Scenes.add_scene(Scenes.new_scene("scene0", begin, step, end), false);
        Core.run(120.0f);
    }
    atexit(Core.quit);
}