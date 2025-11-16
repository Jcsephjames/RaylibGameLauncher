#include <math.h>
#include "animations.h"
#include "../launcher.h"

// CARD ANIMATIONS

void updateCardAnimation(CardAnimationState* anim_state, int current_selection) {
    // Check if selection changed
    if (current_selection != anim_state->selected_card_index) {
        anim_state->previous_card_index = anim_state->selected_card_index;
        anim_state->selected_card_index = current_selection;
        anim_state->is_animating = true;
        anim_state->animation_progress = 0.0f;
    }
    
    // Update animation progress
    if (anim_state->is_animating) {
        float delta_time = GetFrameTime();
        float animation_speed = 2.5f; // Controls how fast the animation plays
        anim_state->animation_progress += delta_time * animation_speed;
        
        // Animation completes in two phases: grow+tilt (0-0.5), shrink back (0.5-1.0)
        if (anim_state->animation_progress >= 1.0f) {
            anim_state->animation_progress = 1.0f;
            anim_state->is_animating = false;
        }
    }
}

void drawAnimatedGameCard(GameCard* card, bool is_selected, CardAnimationState* anim_state, Color selected_color, Color default_color) {
    bool should_animate = (anim_state->is_animating && card->index == anim_state->selected_card_index);
    
    float scale = 1.0f;
    float rotation = 0.0f;
    
    if (should_animate) {
        float t = anim_state->animation_progress;
        
        if (t <= 0.5f) {
            // Phase 1: Grow and tilt (0.0 to 0.5)
            float phase_t = t / 0.5f; // 0.0 to 1.0 in first half
            scale = 1.0f + (0.15f * phase_t); // Grow to 1.15x
            rotation = 3.0f * phase_t; // Tilt up to 3 degrees (left up, right down = positive rotation)
        } else {
            // Phase 2: Shrink back to normal (0.5 to 1.0)
            float phase_t = (t - 0.5f) / 0.5f; // 0.0 to 1.0 in second half
            scale = 1.15f - (0.15f * phase_t); // Shrink from 1.15x to 1.0x
            rotation = 3.0f - (3.0f * phase_t); // Rotate back from 3 degrees to 0
        }
    }
    
    Color border_color = is_selected ? selected_color : default_color;
    Color text_color = is_selected ? selected_color : GRAY;
    
    // Calculate center point for rotation
    float center_x = card->x + card->width / 2.0f;
    float center_y = card->y + card->height / 2.0f;
    
    // Calculate scaled dimensions
    float scaled_width = card->width * scale;
    float scaled_height = card->height * scale;
    
    Vector2 origin = {scaled_width / 2.0f, scaled_height / 2.0f};
    
    // Draw semi-transparent fill for depth effect
    Color border_fill = border_color;
    border_fill.a = 50; // Semi-transparent fill for border effect
    DrawRectanglePro((Rectangle){center_x, center_y, scaled_width, scaled_height}, origin, rotation, border_fill);
    
    // Draw outline lines using corner calculation
    float half_w = scaled_width / 2.0f;
    float half_h = scaled_height / 2.0f;
    float cos_r = cosf(rotation * DEG2RAD);
    float sin_r = sinf(rotation * DEG2RAD);
    
    // Calculate rotated corners
    Vector2 corners[4];
    corners[0] = (Vector2){-half_w, -half_h}; // Top-left
    corners[1] = (Vector2){half_w, -half_h};  // Top-right
    corners[2] = (Vector2){half_w, half_h};   // Bottom-right
    corners[3] = (Vector2){-half_w, half_h};  // Bottom-left
    
    // Rotate corners
    for (int i = 0; i < 4; i++) {
        float x = corners[i].x;
        float y = corners[i].y;
        corners[i].x = (x * cos_r - y * sin_r) + center_x;
        corners[i].y = (x * sin_r + y * cos_r) + center_y;
    }
    
    // Draw lines connecting corners
    DrawLineEx(corners[0], corners[1], 2.0f, border_color);
    DrawLineEx(corners[1], corners[2], 2.0f, border_color);
    DrawLineEx(corners[2], corners[3], 2.0f, border_color);
    DrawLineEx(corners[3], corners[0], 2.0f, border_color);
    
    // Draw text (positioned below, no rotation applied to text for readability)
    int text_y = card->y + card->height + 10;
    if (should_animate) {
        // Adjust text position slightly based on scale
        text_y = (int)(card->y + (card->height * scale / 2.0f) + card->height / 2.0f + 10);
    }
    DrawText(card->name, card->x + 10, text_y, 20, text_color);
}

// HEADER BAR ANIMATIONS

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
) {
    // Calculate total width
    int total_width = 0;
    for (int i = 0; i < label_count; i++) {
        total_width += MeasureText(labels[i], font_size);
        if (i < label_count - 1) total_width += spacing;
    }
    
    // Center the header bar
    int header_x = x + (width / 2) - (total_width / 2);
    int current_x = header_x;
    
    int target_x = 0;
    int target_width = 0;
    
    // Draw labels
    for (int i = 0; i < label_count; i++) {
        int w = MeasureText(labels[i], font_size);
        Color col = (selected_index == i) ? selected_color : default_color;
        
        DrawText(labels[i], current_x, y, font_size, col);
        
        if (i == selected_index) {
            target_x = current_x;
            target_width = w;
        }
        
        current_x += w + spacing;
    }
    
    // Initialize underline on first frame
    if (!underline_state->initialized) {
        underline_state->x = (float)target_x;
        underline_state->width = (float)target_width;
        underline_state->initialized = true;
    }
    
    // Smooth animation
    float ease = 0.25f;
    underline_state->x += ((float)target_x - underline_state->x) * ease;
    underline_state->width += ((float)target_width - underline_state->width) * ease;
    
    // Draw underline
    int underline_y = y + font_size + 5;
    DrawRectangle(
        (int)underline_state->x,
        underline_y,
        (int)underline_state->width,
        4,
        selected_color
    );
}

