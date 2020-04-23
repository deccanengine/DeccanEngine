#define DECCAN_SHORT_NAMES
#define DECCAN_REPORTS_ENABLED
#include "src/deccan.h"
#include "player.h"

Timer timer;

void begin() {
    /* Start here */
    //Asset.load_texture("arrow", "arrow0.png");
    Object.instantiate_object(Object.new_object("main player", "player", NULL_OBJFUNC, _player_begin, _player_step, _player_render, _player_end));
    timer = Deccan_Clock.new_timer();
    timer.start(&timer);
}

void step() {
    /* Start here */
}

void render() {
    Renderer.clear(ColorList.white);

    /* Start here */
    if(Input.key_released(Key.space) && timer.get_time_ms(&timer) > 200) {
        GameObject *s = Object.new_object("circle", "static", NULL_OBJFUNC, _none_begin, _none_step, _none_render, _none_end);
        s->position.x = Object.get_object("main player")->position.x + 10;
        s->position.y = Object.get_object("main player")->position.y + 10;
        Object.instantiate_object(s);
        
        timer.reset(&timer);
    }
    
    if(Input.key_released(Key.up)) {
        Vector2f size = Renderer.get_pixel_size();
        size.x += 0.1f;
        size.y += 0.1f; 
        Renderer.set_pixel_size(size);
    }
    else if(Input.key_released(Key.down)) {
        Vector2f size = Renderer.get_pixel_size();
        size.x -= size.x ? 0.1f : 0.0f; 
        size.y -= size.y ? 0.1f : 0.0f;
        Renderer.set_pixel_size(size);
    }

    if(Input.key_released(Key.left)) {
        Vector2i mode = Core.get_mode();
        mode.x += 40;
        mode.y += 40; 
        Core.set_mode(mode);
    }
    else if(Input.key_released(Key.right)) {
        Vector2i mode = Core.get_mode();
        mode.x -= mode.x > 40 ? 40 : 0;
        mode.y -= mode.y > 40 ? 40 : 0; 
        Core.set_mode(mode);
    }
    
    if(Input.key_released(Key.v)) {
        Core.set_vsync_status(false);
    }
}

void end() {
    /* Start here */
}

int main(int argc, char **argv) {
    if(Core.init("Test", (Vector2i){640, 320})) {
        Scenes.add_scene(Scenes.new_scene("scene0", begin, step, render, end), false);
        Core.run(120.0f);
    }
    atexit(Core.quit);
}