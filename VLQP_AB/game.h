#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "level.h"
#include "enemies.h"
#include "elements.h"
#include "bullet.h"
#include "door.h"

extern byte level;
extern byte displayLevel;

// methods prototypes ////////////////////////////////////////////////////////

void stateGamePlaying();
void stateGameNextLevel();
void stateGamePrepareLevel();
void stateGameOver();
void stateGamePause();
void checkPause();

#endif
