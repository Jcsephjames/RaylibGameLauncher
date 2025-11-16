#pragma once
#ifndef UI_COMMON_H
#define UI_COMMON_H

#include <raylib.h>

// STRUCTS

// Game Card Structure
typedef struct {
    int x;
    int y;
    int width;
    int height;
    const char* name;
    int index;  // Position in grid (0-8)
} GameCard;

// Selection State Structure
typedef struct {
    int selected_index;
    int max_options;
    bool is_active;
} SelectionState;

// GAME CARD FUNCTIONS
void drawGameCard(GameCard* card, bool is_selected, Color selected_color, Color default_color);
int getGameCardX(int index, int card_width, int margin, int spacing);
int getGameCardY(int index, int card_height, int margin, int spacing);

// BORDER FUNCTIONS
void drawBorder(int x, int y, int width, int height, int thickness, Color color);
void drawMultiBorder(int x, int y, int width, int height, int thickness, Color color);

// NAVIGATION HELPERS
int wrapIndex(int index, int max, int min);
int clampIndex(int index, int min, int max);

#endif // UI_COMMON_H

