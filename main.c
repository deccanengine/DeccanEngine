#define using_namespace_Deccan
#include "src/deccan.h"

void begin() {
    /* Start here */
    Asset.load_texture("arrow", "arrow0.png");
}

int x = 100, y = 100;

void step() {
    Renderer.clear(ColorList.white);

    /* Start here */
    if(Input.key_held(Key.w)){ y-=1; }
    else if(Input.key_held(Key.s)){ y+=1; }
    else if(Input.key_held(Key.a)){ x-=1; }
    else if(Input.key_held(Key.d)){ x+=1; }
    
    Color col;
    Vector2i pos = Input.get_mouse_pos();
    if(pos.x > x && pos.x < x+50 && pos.y > y && pos.y < y+50) {
        if(Input.button_down(Button.left)) {
            col = ColorList.green;
        }
        else { col = ColorList.dark_green; }
    }
    else {
        col = ColorList.black;
    }
    Renderer.draw_rect((Rect){x, y, 50, 50}, true, col);
    Renderer.draw_circle((Vector3i){x+100, y+100, 50}, true, col);
    Renderer.draw_texture((Vector2i){200, 200}, Asset.get_texture("arrow"));
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