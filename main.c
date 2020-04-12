#define using_namespace_Deccan
#include "deccan.h"

void begin() {
    /* Start here */
    Asset.load_texture("arrow", "arrow0.png");
}

int x = 100, y = 100;

void step() {
    Renderer.clear((Color){255, 255, 255, 255});

    /* Start here */
    if(Input.get_key(Key.w).is_held){ y-=1; }
    else if(Input.get_key(Key.s).is_held){ y+=1; }
    else if(Input.get_key(Key.a).is_held){ x-=1; }
    else if(Input.get_key(Key.d).is_held){ x+=1; }
    
    Vector2i pos = Input.get_mouse_pos();
    if(pos.x > x && pos.x < x+50 && pos.y > y && pos.y < y+50) {
        if(Input.get_mouse_button(Button.left).is_down) {
            Renderer.set_color((Color){0, 255, 0, 255});
        }
        else { Renderer.set_color((Color){0, 180, 0, 255}); }
    }
    else {
        Renderer.set_color(black);
    }
    SDL_RenderFillRect(Core.get_global_engine()->renderer, &(SDL_Rect){x, y, 50, 50});
    
    int w, h;
    SDL_Texture *tex = Asset.get_texture("arrow");
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_RenderCopy(Core.get_global_engine()->renderer, tex, NULL, &(SDL_Rect){x, y, w, h});
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