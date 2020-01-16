#ifndef GLOBALS_H
#define GLOBALS_H

#include "Arglib.h"

// constants /////////////////////////////////////////////////////////////////

//define menu states (on main menu)
#define STATE_MENU_INTRO         0
#define STATE_MENU_MAIN          1
#define STATE_MENU_HELP          2
#define STATE_MENU_PLAY          3
#define STATE_MENU_INFO          4
#define STATE_MENU_SOUNDFX       5

//define game states (on main menu)

#define STATE_GAME_PREPARE_LEVEL 6
#define STATE_GAME_NEXT_LEVEL    7
#define STATE_GAME_PLAYING       8
#define STATE_GAME_OVER          9
#define STATE_GAME_PAUSE         10

// globals ///////////////////////////////////////////////////////////////////

extern Arduboy arduboy;
extern Sprites sprites;
extern byte gameState;
extern unsigned long scorePlayer;
extern byte globalCounter;

#endif

// function prototypes ///////////////////////////////////////////////////////

short burp(short start, short goal, unsigned char step);
