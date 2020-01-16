#ifndef MENU_BITMAPS_H
#define MENU_BITMAPS_H

#include "game.h"
#include "globals.h"

// globals ///////////////////////////////////////////////////////////////////

extern byte menuSelection;
extern byte level;
extern byte displayLevel;


// method prototypes /////////////////////////////////////////////////////////

void stateMenuIntro();
void stateMenuMain();
void stateMenuHelp();
void stateMenuPlay();
void stateMenuInfo();
void stateMenuSoundfx();


#endif
