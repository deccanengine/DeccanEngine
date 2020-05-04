#define DECCAN_SHORT_NAMES
#include "src/deccan.h"
#include "player.h"

Timer timer;

void begin() {
    /* Start here */
    //Asset.load_texture("arrow", "arrow0.png");
    Object.InstantiateObject(Object.NewObject("main player", "player", NULL_OBJFUNC, _player_begin, _player_step, _player_render, _player_end));
    timer = Clock.NewTimer();
    timer.Start(&timer);
}

void step() {
    /* Start here */
}

void render() {
    Renderer.Clear(ColorList.white);

    /* Start here */
    if(Input.KeyReleased(Key.space) && timer.GetTimeMS(&timer) > 200) {
        GameObject *s = Object.NewObject("circle", "static", NULL_OBJFUNC, _none_begin, _none_step, _none_render, _none_end);
        s->position.x = Object.GetObject("main player")->position.x + 10;
        s->position.y = Object.GetObject("main player")->position.y + 10;
        Object.InstantiateObject(s);
        
        timer.Reset(&timer);
    }
    
    if(Input.KeyReleased(Key.up)) {
        Vector2f size = Renderer.GetPixelSize();
        size.x += 0.1f;
        size.y += 0.1f; 
        Renderer.SetPixelSize(size);
    }
    else if(Input.KeyReleased(Key.down)) {
        Vector2f size = Renderer.GetPixelSize();
        size.x -= size.x ? 0.1f : 0.0f; 
        size.y -= size.y ? 0.1f : 0.0f;
        Renderer.SetPixelSize(size);
    }

    if(Input.KeyReleased(Key.left)) {
        Vector2i mode = Core.GetMode();
        mode.x += 40;
        mode.y += 40; 
        Core.SetMode(mode);
    }
    else if(Input.KeyReleased(Key.right)) {
        Vector2i mode = Core.GetMode();
        mode.x -= mode.x > 40 ? 40 : 0;
        mode.y -= mode.y > 40 ? 40 : 0; 
        Core.SetMode(mode);
    }
    
    if(Input.KeyReleased(Key.v)) {
        Core.SetVsyncStatus(false);
    }
}

void end() {
    /* Start here */
}

int main(int argc, char **argv) {
    if(Core.Init("Test", (Vector2i){640, 320})) {
        Scene.AddScene(Scene.NewScene("scene0", begin, step, render, end), false);
        Core.Run(120.0f);
    }
    atexit(Core.Quit);
}