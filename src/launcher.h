#pragma once
#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <raylib.h>

// Constants
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TARGET_FPS 60

#define CENTER_X SCREEN_WIDTH/2
#define CENTER_Y SCREEN_HEIGHT/2

#define TITLE_BAR_HEIGHT 40


#define GAMES_TOP_MARGIN 100
#define GAMES_LEFT_MARGIN 40
#define GAMES_RIGHT_MARGIN 40
#define GAMES_BOTTOM_MARGIN 40
#define GAMES_MARGIN_BETWEEN 40

// Launcher Variables
extern int launcher_Menu_State; // 0 = Default launcher controls, 1 = Profile Overlay

// Selection Variables
extern bool launcher_Top_Menu_Bool; // true = Top Menu, false = Game Selection
extern int launcher_Menu_Selection;
extern int number_Of_Options;

extern bool launcher_Game_Menu_Bool; // true = Game Selection, false = Top Menu
extern int launcher_Games_Selection_X;
extern int launcher_Games_Selection_Y;
extern int number_Of_Games;

// main.py Variables
extern int main_State; // 0 = Launcher, 1 = a Game





// Function Prototypes
void initLauncherMenu(void);
void launcherMenu(void);

void menu_Settings_Selection(void);

void drawLauncherMenu(void);
void updateLauncherMenu(void);

// Profile overlay functions
void updateProfileOverlay(void);
void drawProfileOverlay(void);

// Settings menu functions
void updateSettingsMenu(void);
void drawSettingsMenu(void);

#endif // LAUNCHER_H