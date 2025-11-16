#include <raylib.h>
#include "profile.h"
#include "../launcher.h"
#include "settings.h"
#include "../ui/ui_common.h"
#include "../ui/animations.h"

// Global Variables

const char *game_names[9] = {
    "GamblePong", "Blox Breaker", "Star Shooter",
    "Game 4", "Game 5", "Game 6",
    "Game 7", "Game 8", "Game 9"
};

int selected_games_index = 0; // This and the line below is the number of available options for games and headers respectivily
int profile_selected_headers_index = 0;

bool profile_headers_selection_bool;
bool profile_games_selection_bool;


void initProfile(){
    profile_headers_selection_bool = true;
    profile_games_selection_bool = false;
}
// Login Prompt
void drawLoginPrompt(void) {
    BeginDrawing();

    int prompt_x = 300;
    int prompt_y = 300;
    int prompt_width = SCREEN_WIDTH - 320;
    int prompt_height = SCREEN_HEIGHT - 320;
    drawBorder(prompt_x, prompt_y, prompt_width, prompt_height, 3, launcher_Text_Color);

    EndDrawing();
}
void updateLoginPrompt(void) {
    if (IsKeyPressed(KEY_BACKSPACE)) {
        extern int launcher_Menu_State;
        launcher_Menu_State = 0;
    }
}

// Profile Overlay (draw)
void drawProfileOverlay(void) {
    BeginDrawing();
    ClearBackground(launcher_Bg_Color);

    drawProfileLeftElement();
    drawCenterProfileElement();

    EndDrawing();
}

// Left Element (1/3 width)
void drawProfileLeftElement(void) {
    int third_width = SCREEN_WIDTH / 3;
    int left_width = third_width - PROFILE_STANDARD_MARGIN * 2;
    int left_x = PROFILE_STANDARD_MARGIN;
    int left_y = PROFILE_STANDARD_MARGIN;
    int left_height = SCREEN_HEIGHT - PROFILE_STANDARD_MARGIN * 2;

    // BORDER
    drawBorder(left_x, left_y, left_width, left_height, 3, launcher_Text_Color);

    // PROFILE IMAGE
    int img_size = 200;
    int img_x = left_x + 20;
    int img_y = left_y + 20;

    drawBorder(img_x, img_y, img_size, img_size, 2, launcher_Text_Color);

    // USERNAME
    DrawText("Username:", img_x + img_size + 20, img_y + 10, 20, launcher_Text_Color);

    // STATS SECTION
    int stats_y = img_y + img_size + 40;

    DrawText("OVERALL STATISTICS", img_x, stats_y, 22, launcher_Text_Color);

    for (int i = 0; i < 2; i++) {
        DrawLine(img_x, stats_y + 25 + i,
            img_x + MeasureText("OVERALL STATISTICS", 22),
            stats_y + 25 + i,
            launcher_Text_Color);
    }

    DrawText("Games Played: 0", img_x, stats_y + 40, 20, launcher_Text_Color);
    DrawText("Hours Played: 0", img_x, stats_y + 70, 20, launcher_Text_Color);
    DrawText("Total Wins: 0", img_x, stats_y + 100, 20, launcher_Text_Color);
    DrawText("Total Losses: 0", img_x, stats_y + 130, 20, launcher_Text_Color);
}


// Center/Right Element (2/3 width)
static UnderlineState profile_underline_state = {0.0f, 0.0f, false};

void drawCenterProfileElement(void) {
    int third_width = SCREEN_WIDTH / 3;

    int right_x = third_width + PROFILE_STANDARD_MARGIN;
    int right_y = (int)(SCREEN_HEIGHT * 0.33f); // Bottom Boarder Needs to take up 2/3s of the screen
    int right_width = SCREEN_WIDTH - right_x - PROFILE_STANDARD_MARGIN;
    int right_height = SCREEN_HEIGHT - right_y - PROFILE_STANDARD_MARGIN;

    // BORDER
    drawBorder(right_x, right_y, right_width, right_height, 3, launcher_Text_Color);

    // HEADER BAR
    int header_X = third_width + PROFILE_STANDARD_MARGIN;
    int header_Y = PROFILE_STANDARD_MARGIN + 10;
    
    const char *header_labels[] = {
        "High Scores", "Achievements", "Global Rankings", "Friends"
    };
    drawAnimatedHeaderBar(
        header_labels, 4,
        header_X, right_width, header_Y,
        20, 40,
        profile_selected_headers_index,
        &profile_underline_state,
        launcher_Text_Color,
        GRAY
    );

    // SELECTED GAME NAME
    DrawText(game_names[selected_games_index],
        header_X + 10, right_y - 50,
        30, launcher_Text_Color);
}


// Input / Update Handling

void updateProfileOverlay(void) {
    if (profile_headers_selection_bool) {
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
            profile_selected_headers_index = (profile_selected_headers_index + 1) % 4;

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            profile_selected_headers_index--;
            if (profile_selected_headers_index < 0) profile_selected_headers_index = 3;
        }

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            profile_headers_selection_bool = false;
            profile_games_selection_bool = true;
        }
    }

    if (profile_games_selection_bool) {
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
            selected_games_index = (selected_games_index + 1) % 9;

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            selected_games_index--;
            if (selected_games_index < 0) selected_games_index = 8;
        }

        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            profile_headers_selection_bool = true;
            profile_games_selection_bool = false;
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        profile_selected_headers_index = 0; // Reset Profile Header Selection
        
        extern int launcher_Menu_State;
        launcher_Menu_State = 0;
    }
}
