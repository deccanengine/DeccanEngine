#pragma once
#include "Config.h"
#include "Math/Vector2.h"

typedef struct CoreSettings {
    char *title;
    Vector2 resolution;
    bool fullscreen;
    bool vsync;
    bool closeOnEscape;
    float fps;
} CoreSettings;

static inline CoreSettings CoreSettings_New() {
    CoreSettings settings = {
        .title = "Deccan App",
        .resolution = (Vector2){800, 600},
        .fullscreen = false,
        .vsync = false,
        .closeOnEscape = true,
        .fps = 60.0f
    };

    return settings;
}