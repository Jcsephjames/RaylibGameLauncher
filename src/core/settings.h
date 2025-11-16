#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

#include <raylib.h>

// CONSTANTS
#define SETTINGS_STANDARD_MARGIN 20

#define BOARDER_THICKNESS 3

// General Variables
extern bool accessibilitySettingsBool;

extern const char *game_names[9];
extern int selected_games_index;
extern int settings_selected_headers_index;


extern bool settings_header_selection_bool;
extern bool settings_game_selection_bool;

extern int header_count;

// COLOR VARIABLES
extern Color launcher_Bg_Color;
extern Color title_Text_Color;
extern Color launcher_Text_Color;

extern Color orange_Red;
extern Color black;


// FUNCTION PROTOTYPES
void initSettings(void);
void updateSettingsMenu(void);
void drawSettingsMenu(void);

void drawSettingsLeftElement(void);
void drawSettingsRightElement(void);


void colorsAndThemes(void);


#endif // SETTINGS_H