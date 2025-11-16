#include <raylib.h>
#include "settings.h"
#include "../launcher.h"
#include "../ui/ui_common.h"
#include "../ui/animations.h"


bool accessibilitySettingsBool = false;

Color launcher_Bg_Color = {0, 0, 0, 255};
Color title_Text_Color = {255, 255, 255, 255};
Color launcher_Text_Color = {255, 255, 255, 255};

Color orange_Red = {255, 69, 0, 255};
Color black = {0, 0, 0, 255};

// LEFT HEADER LIST
const char *settings_left_headers[4] = {
    "General Settings",
    "Custom",
    "Accessibility",
    "Animations"
};

int selected_settings_left_header = 0;

int settings_selected_headers_index = 0;


bool settings_header_selection_bool;
bool settings_game_selection_bool;

void initSettings(void) {
    settings_header_selection_bool = true;
    settings_game_selection_bool = false;
    colorsAndThemes();
}


void drawSettingsMenu(void) {
    BeginDrawing();
    ClearBackground(launcher_Bg_Color);

    drawSettingsLeftElement();
    drawSettingsRightElement();

    EndDrawing();
}


// Left Element (2/3 width)
static UnderlineState settings_underline_state = {0.0f, 0.0f, false};

void drawSettingsLeftElement(void)
{
    int two_thirds_width = (SCREEN_WIDTH * 2) / 3;
    int left_x = SETTINGS_STANDARD_MARGIN;
    int left_width = two_thirds_width - SETTINGS_STANDARD_MARGIN * 2;
    int left_y = SETTINGS_STANDARD_MARGIN;
    int left_height = SCREEN_HEIGHT - SETTINGS_STANDARD_MARGIN * 2;

    // BORDER
    drawBorder(left_x, left_y, left_width, left_height, BOARDER_THICKNESS, launcher_Text_Color);

    // HEADER BAR (side by side headers)
    const char *header_labels[] = {
        "General", "Themes", "Display", "Audio", "Controls"
    };
    drawAnimatedHeaderBar(
        header_labels, 5,
        left_x, left_width, left_y + 20,
        20, 35,
        settings_selected_headers_index,
        &settings_underline_state,
        launcher_Text_Color,
        GRAY
    );
}

// Right Element (1/3 width)
void drawSettingsRightElement(void) {
    int third_width = SCREEN_WIDTH / 3;

    int right_x = third_width * 2 + SETTINGS_STANDARD_MARGIN;
    int right_y = (int)(SCREEN_HEIGHT * 0.33f);
    int right_width = third_width - SETTINGS_STANDARD_MARGIN * 2;
    int right_height = SCREEN_HEIGHT - right_y - SETTINGS_STANDARD_MARGIN;

    // BORDER
    drawBorder(right_x, right_y, right_width, right_height, 3, launcher_Text_Color);

    // HEADER BAR (centered)
    const char *header_labels[] = { "Game Settings" };
    int font_size = 22;

    int text_width = MeasureText(header_labels[0], font_size);
    int text_x = right_x + (right_width / 2) - (text_width / 2);

    DrawText(header_labels[0], text_x, SETTINGS_STANDARD_MARGIN + 10, font_size, launcher_Text_Color);

    // SELECTED GAME
    int game_text_width = MeasureText(game_names[selected_games_index], 28);
    int game_text_x = right_x + (right_width / 2) - (game_text_width / 2);

    DrawText(game_names[selected_games_index], game_text_x, right_y - 50, 30, launcher_Text_Color);
}
// Input / Update Handling
void updateSettingsMenu(void) {
    // SELECT HEADER LIST (LEFT PANEL)
    int header_count = 5;
    if (settings_header_selection_bool) {
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
            settings_selected_headers_index++;

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
            settings_selected_headers_index--;

        if (settings_selected_headers_index < 0) settings_selected_headers_index = header_count - 1;
        if (settings_selected_headers_index >= header_count) settings_selected_headers_index = 0;
    }
    // SELECT GAME LIST (RIGHT PANEL)
    if (settings_game_selection_bool) {
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
            selected_games_index = (selected_games_index + 1) % 9;

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            selected_games_index--;
            if (selected_games_index < 0) selected_games_index = 8;
        }
    }
    if (IsKeyPressed(KEY_ENTER)) {
        settings_game_selection_bool = !settings_game_selection_bool;
        settings_header_selection_bool = !settings_header_selection_bool;
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        settings_selected_headers_index = 0; // Reset Settings Header Selection

        extern int launcher_Menu_State;
        launcher_Menu_State = 0;
    }
}

// THEMES
void colorsAndThemes(void) {
    launcher_Bg_Color = black;
    title_Text_Color = orange_Red;
}
