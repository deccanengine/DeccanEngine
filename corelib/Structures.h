#pragma once
#include "Config.h"
//#include "Math/Vector2.h"

typedef struct CoreSettings {
    char *title;
    vec2 resolution;
    bool fullscreen;
    bool vsync;
    bool resizable;
    bool closeOnEscape;
    float fps;
} CoreSettings;

/*static inline CoreSettings CoreSettings_New() {
    CoreSettings settings = {
        .title = "Deccan App",
        .resolution = (vec2){800, 600},
        .fullscreen = false,
        .vsync = false,
        .resizable = false,
        .closeOnEscape = true,
        .fps = 60.0f
    };

    return settings;
}*/
