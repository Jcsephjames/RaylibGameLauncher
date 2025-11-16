#include <raylib.h>
#include "launcher.h"

int main_State = 0;

int main(void) {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Launcher");
    SetTargetFPS(TARGET_FPS);

    initLauncherMenu();
    
    while (!WindowShouldClose()) {
        switch(main_State)
        {
            case 0:
                launcherMenu();
                break;
            case 1:
                // Code to launch a game would go here
                break;
        }
    }

    CloseWindow();
    return 0;
}
