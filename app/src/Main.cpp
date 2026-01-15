#include "raylib.h"
#include <stdio.h>
#include "Scene.h"

int main()
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "Rastering");
    //SetTargetFPS(60);

    const char* app_dir = GetApplicationDirectory();
    TraceLog(LOG_INFO, "Bin directory: %s", app_dir);
    ChangeDirectory(app_dir);

    char title[100];

    Scene scene{screenWidth, screenHeight};
    while (!WindowShouldClose()) 
    {
        static float elapsed = 0;
        
        float delta_time = GetFrameTime();
        int fps = GetFPS();

        elapsed += delta_time;
        if (elapsed >= 1.f) {
            elapsed -= 1.f;
            sprintf(title, "Delta: %.4f - FPS: %d", delta_time, fps);
            SetWindowTitle(title);
        }

        BeginDrawing();
            ClearBackground(BLACK);

            scene.Update(delta_time);

        EndDrawing();
    }

    scene.Destroy();

    CloseWindow();
    return 0;
}