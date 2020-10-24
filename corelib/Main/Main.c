/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Deccan.h"

bool DE_AppInit(DeccanSettings *settings) {
    Core_Init(settings);

    /* Create renderer */
    Renderer_Init(DE_Core_GetWindowHandle());

    return true;
}

void DE_AppUpdate() {
    DeccanTimer fpsTimer;
    DeccanTimer frmTimer;

    DE_TimerStart(&fpsTimer);    /* To calculate FPS */

    int32_t frameCount;
    float fpsAverage = 0.0f;
    float deltaTime = 0.0f;

    DeccanSettings *settings = DE_Core_GetSettings();

    while(Core_IsRunning()) {
        DE_TimerStart(&frmTimer);

        /* Calculate FPS */
        fpsAverage = frameCount / DE_TimerGetTime(&fpsTimer).seconds;
        if(fpsAverage > 20000) {
            fpsAverage = 0.0f;
        }

        DE_Core_Update(fpsAverage, deltaTime);

        /* Render the background before rendering anything */
        Renderer_Background();
        DE_SceneUpdate();

        /* Render everything */
        Renderer_Present();

        /* Increment the frame counter */
        frameCount++;

        /* Current ticks per frame i.e delta time */
        deltaTime = DE_TimerGetTime(&frmTimer).milliseconds;

        /* Limit FPS */
        if((!settings->vsync) &&
           (settings->fps > 20.0f)) {
            float ticksPerFrame = (1000.0f / settings->fps);  /* Required ticks per frame */
            if(deltaTime < ticksPerFrame) {
                DE_ClockDelay((int)(ticksPerFrame - deltaTime));
            }
        }
    }
}

void DE_AppQuit() {
    DE_SceneQuit();

    DE_SceneFreeAll();

    Renderer_Quit();

    Core_Quit();
}
