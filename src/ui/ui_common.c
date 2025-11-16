#include "ui_common.h"
#include "../launcher.h"

// GAME CARDS

void drawGameCard(GameCard* card, bool is_selected, Color selected_color, Color default_color) {
    Color border_color = is_selected ? selected_color : default_color;
    Color text_color = is_selected ? selected_color : GRAY;
    
    DrawRectangleLines(card->x, card->y, card->width, card->height, border_color);
    DrawText(card->name, card->x + 10, card->y + card->height + 10, 20, text_color);
}

int getGameCardX(int index, int card_width, int margin, int spacing) {
    int col = index % 3;
    return margin + (col * (card_width + spacing));
}

int getGameCardY(int index, int card_height, int margin, int spacing) {
    int row = index / 3;
    return margin + (row * (card_height + spacing));
}

// BORDER FUNCTIONS

void drawBorder(int x, int y, int width, int height, int thickness, Color color) {
    for (int i = 0; i < thickness; i++) {
        DrawRectangleLines(x - i, y - i, width + 2 * i, height + 2 * i, color);
    }
}

void drawMultiBorder(int x, int y, int width, int height, int thickness, Color color) {
    // Same as drawBorder, kept for compatibility with existing code
    drawBorder(x, y, width, height, thickness, color);
}

// NAVIGATION HELPERS

int wrapIndex(int index, int max, int min) {
    if (index > max) return min;
    if (index < min) return max;
    return index;
}

int clampIndex(int index, int min, int max) {
    if (index > max) return max;
    if (index < min) return min;
    return index;
}

