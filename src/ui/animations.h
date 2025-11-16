#pragma once
#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <raylib.h>
#include "ui_common.h"

// ANIMATION STRUCTS

// Underline Animation State
typedef struct {
    float x;
    float width;
    bool initialized;
} UnderlineState;

// Card Animation State
typedef struct {
    int selected_card_index;
    int previous_card_index;
    float animation_progress;  // 0.0 to 1.0
    bool is_animating;
} CardAnimationState;

// ANIMATION FUNCTIONS

// Card Animations
void updateCardAnimation(CardAnimationState* anim_state, int current_selection);
void drawAnimatedGameCard(GameCard* card, bool is_selected, CardAnimationState* anim_state, Color selected_color, Color default_color);

// Header Bar Animations
void drawAnimatedHeaderBar(
    const char** labels, 
    int label_count, 
    int x, int width, int y,
    int font_size,
    int spacing,
    int selected_index,
    UnderlineState* underline_state,
    Color selected_color,
    Color default_color
);

#endif // ANIMATIONS_H

