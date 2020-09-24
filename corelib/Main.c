/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Deccan.h"

bool DE_App_Init(DeccanSettings *settings) {
    Core_Init(settings);

    /* Create renderer */
    Renderer_Init(DE_Core_GetWindowHandle());

    return true;
}

void DE_App_Update() {
    Timer fpsTimer;
    Timer frmTimer;

    Clock_StartTimer(&fpsTimer);    /* To calculate FPS */

    int32_t frameCount;
    float fpsAverage = 0.0f;
    float deltaTime = 0.0f;

    DeccanSettings *settings = DE_Core_GetSettings();

    while(Core_IsRunning()) {
        Clock_StartTimer(&frmTimer);

        /* Calculate FPS */
        fpsAverage = frameCount / Clock_GetTime(&fpsTimer).seconds;
        if(fpsAverage > 20000) {
            fpsAverage = 0.0f;
        }

        DE_Core_Update(fpsAverage, deltaTime);

        /* Render the background before rendering anything */
        Renderer_Background();
        Scene_Update();

        /* Render everything */
        Renderer_Present();

        /* Increment the frame counter */
        frameCount++;

        /* Current ticks per frame i.e delta time */
        deltaTime = Clock_GetTime(&frmTimer).milliseconds;

        /* Limit FPS */
        if((!settings->vsync) &&
           (settings->fps > 20.0f)) {
            float ticksPerFrame = (1000.0f / settings->fps);  /* Required ticks per frame */
            if(deltaTime < ticksPerFrame) {
                Clock_Delay((int)(ticksPerFrame - deltaTime));
            }
        }
    }
}

void DE_App_Quit() {
    Scene_Quit();

    Scene_FreeAll();

    Renderer_Quit();

    Core_Quit();
}
