#pragma once
#ifndef PROFILE_H
#define PROFILE_H


#include <raylib.h>


// ------------------ Constants (SCREAMING_SNAKE_CASE) ------------------
#define PROFILE_STANDARD_MARGIN 20


// ------------------ External Data (variables = snake_case) ------------------
extern const char *game_names[9];
extern int selected_games_index;
extern int profile_selected_headers_index;


extern bool profile_headers_selection_bool;
extern bool profile_games_selection_bool;


// ------------------ Function Prototypes (camelCase) ------------------
void initProfile(void);
void drawLoginPrompt(void);
void updateLoginPrompt(void);


void drawProfileOverlay(void);
void drawProfileLeftElement(void);
void drawCenterProfileElement(void);


void updateProfileOverlay(void);


#endif // PROFILE_H