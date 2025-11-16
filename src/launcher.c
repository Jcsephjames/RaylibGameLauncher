#include <stdio.h>
#include <raylib.h>

#include "launcher.h"
#include "core/settings.h"
#include "core/profile.h"
#include "ui/ui_common.h"
#include "ui/animations.h"

int launcher_Menu_State = 0; // 0 = Game Selection Area, 1 = Settings Overlay, 2 = Profile Overlay

bool launcher_Top_Menu_Bool = true; // true = Top Menu, false = Game Selection
int launcher_Menu_Selection = 0;
int number_Of_Options = 3;


bool launcher_Game_Menu_Bool = false; // true = Game Selection, false = Top Menu
int launcher_Games_Selection_X = 0;
int total_X_Options = 3;
int total_Y_Options = 3;
int launcher_Games_Selection_Y = 0;

int card_x = (SCREEN_WIDTH - (GAMES_LEFT_MARGIN + GAMES_RIGHT_MARGIN) - (GAMES_MARGIN_BETWEEN * 2)) / 3;
int card_y = (SCREEN_HEIGHT - TITLE_BAR_HEIGHT - (GAMES_TOP_MARGIN + GAMES_BOTTOM_MARGIN) - (GAMES_MARGIN_BETWEEN * 2)) / 3;

// Card Animation State
static CardAnimationState card_animation_state = {-1, -1, 0.0f, false};

void initLauncherMenu(void)
{
    // Initialization code for the launcher menu can go here

    initSettings();
    initProfile();
}

void launcherMenu(void)
{

    while (!WindowShouldClose()) {

        switch(launcher_Menu_State)
        {
            case 0:
                updateLauncherMenu();
                drawLauncherMenu();
                break;
            case 1:
                updateSettingsMenu();
                drawSettingsMenu();    
                break;
            case 2:
                updateProfileOverlay();
                drawProfileOverlay();
                break;
            }
    }
}
void drawLauncherMenu(void)
{
    BeginDrawing();
    ClearBackground(launcher_Bg_Color);

    int launcher_Profile_Bar_Spacing = (SCREEN_WIDTH - MeasureText("PROFILE", 35) - 10);
    int launcher_Settings_Bar_Spacing = (launcher_Profile_Bar_Spacing - MeasureText("SETTINGS", 35) - 20);

    // Top Right Menu Text Colors
    Color null_Selection_Color = (launcher_Menu_Selection == 1) ? launcher_Text_Color : GRAY;
    Color settings_Selection_Color = (launcher_Menu_Selection == 2) ? launcher_Text_Color : GRAY;
    Color profile_Selection_Color = (launcher_Menu_Selection == 3) ? launcher_Text_Color : GRAY;

    DrawText("Game Launcher INC", SCREEN_WIDTH - MeasureText("Game Launcher INC", 40) - 10, SCREEN_HEIGHT - TITLE_BAR_HEIGHT, TITLE_BAR_HEIGHT, title_Text_Color);

    // Top Right Menu Options
    DrawText("HOME", 10, 10 , 35, null_Selection_Color);
    DrawText("SETTINGS", launcher_Settings_Bar_Spacing, 10 , 35, settings_Selection_Color);
    DrawText("PROFILE", launcher_Profile_Bar_Spacing, 10 , 35, profile_Selection_Color);

    // Game Selection Grid
    extern const char *game_names[9];
    
    // Calculate current selection index for animation
    int current_selection = -1;
    if (launcher_Game_Menu_Bool) {
        current_selection = (launcher_Games_Selection_Y - 1) * 3 + (launcher_Games_Selection_X - 1);
    }
    
    // Update animation state
    updateCardAnimation(&card_animation_state, current_selection);
    
    // Draw all cards
    for (int i = 0; i < 9; i++) {
        GameCard card = {
            .x = getGameCardX(i, card_x, GAMES_LEFT_MARGIN, GAMES_MARGIN_BETWEEN),
            .y = getGameCardY(i, card_y, GAMES_TOP_MARGIN, GAMES_MARGIN_BETWEEN),
            .width = card_x,
            .height = card_y,
            .name = game_names[i],
            .index = i
        };
        bool is_selected = (launcher_Game_Menu_Bool && i == current_selection);
        
        drawAnimatedGameCard(&card, is_selected, &card_animation_state, launcher_Text_Color, launcher_Text_Color);
    }

    EndDrawing();
}

void updateLauncherMenu(void)
{
    menu_Settings_Selection();

    // Launcher Menu Selection
    if (IsKeyPressed(KEY_ENTER))
    {
        if(launcher_Menu_Selection == 0)
        {
            launcher_Menu_State = 0;
        }
        if(launcher_Menu_Selection == 2)
        {
            launcher_Menu_State = 1; // Switch to Settings Menu
        }
        if(launcher_Menu_Selection == 3)
        {
            launcher_Menu_State = 2; // Switch to Profile Overlay
        }
    }
}
void menu_Settings_Selection(void)
{
    if (launcher_Top_Menu_Bool == true){
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        {
            launcher_Menu_Selection++;
            if (launcher_Menu_Selection > number_Of_Options)
                launcher_Menu_Selection = 1;
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        {
            launcher_Menu_Selection--;
            if (launcher_Menu_Selection < 1)
                launcher_Menu_Selection = number_Of_Options;
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            launcher_Top_Menu_Bool = false; // Switch to Game Selection
            launcher_Game_Menu_Bool = true;
            launcher_Games_Selection_X = 1; // Start at first game
            launcher_Games_Selection_Y = 0; // This needs to be 0 so when user presses down arrow it goes to Y = 1
            launcher_Menu_Selection = 0;
        }
    }
    // Game Selection
    if (launcher_Game_Menu_Bool == true){
        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && launcher_Games_Selection_Y == 1)
        {
            launcher_Top_Menu_Bool = true; // Switch to Top Menu
            launcher_Game_Menu_Bool = false;
            launcher_Games_Selection_X = 0;
            launcher_Games_Selection_Y = 0;
            launcher_Menu_Selection = 1;
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            launcher_Games_Selection_Y++;
            if (launcher_Games_Selection_Y > total_Y_Options)
                launcher_Games_Selection_Y = 1;
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) 
        {
            launcher_Games_Selection_Y--;
            if (launcher_Games_Selection_Y < 1)
                launcher_Games_Selection_Y = total_Y_Options;
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        {
            launcher_Games_Selection_X++;
            if (launcher_Games_Selection_X > total_X_Options)
                launcher_Games_Selection_X = 1;
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        {
            launcher_Games_Selection_X--;
            if (launcher_Games_Selection_X < 1)
                launcher_Games_Selection_X = total_X_Options;
        }
    }
}