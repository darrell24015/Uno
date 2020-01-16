#include "game.h"
#include "enemies.h"
#include "pickup.h"

byte gameOverAndStageFase;
boolean bonusVisible;
boolean nextLevelVisible;
boolean pressKeyVisible;
int leftX;
byte rightX;


// method implementations ////////////////////////////////////////////////////

// stateGamePlaying
// called each frame the gamestate is set to playing
void stateGamePlaying()
{
  // Update Level
  if (!(arduboy.frameCount % (60 * 3))) {
    spawnZombie();
  }

  // Check fo Pause
  checkPause();

  // Update Objects
  updatePlayer(coolGirl);
  updateBullets();
  updateZombies();
  updateSurvivors();

  // Draw
  drawLevel();
  drawDoor();
  drawPickups();
  drawSurvivors();
  drawZombies();
  drawBullets();
  drawPlayer(coolGirl);

  drawNumbers(86, 0, FONT_SMALL, DATA_SCORE);
  drawLife(coolGirl);
  drawAmountSurvivors();
  drawCoolDown();
}

int readSurvivorData(unsigned char index)
{
  return pgm_read_byte(survivorLocation + ((int)level - 1) * 10 + (int)index) * TILE_WIDTH; //PLAYER_WIDTH
}

int readPlayerAndExitData(unsigned char index)
{
  return pgm_read_byte(playerAndExitLocation + ((int)displayLevel - 1) * 4 + (int)index) * TILE_WIDTH; //PLAYER_WIDTH
}

// stateGameNextLevel
// called each frame the gamestate is set to next level
void stateGamePrepareLevel()
{
  clearSurvivors();
  clearPickups();
  clearZombies();

  level++;
  level = (level - 1) % NUM_MAPS + 1;
  displayLevel++;

  pickupsCounter = 0;
  gameOverAndStageFase = 0;
  globalCounter = 0;

  gameState = STATE_GAME_NEXT_LEVEL;
}


void nextLevelStart()
{
  leftX = -52;
  rightX = 164;
  if (displayLevel > 1)
  {
    bonusVisible = true;
    nextLevelVisible = false;
    pressKeyVisible = false;
    gameOverAndStageFase++;
  }
  else
  {
    bonusVisible = false;
    nextLevelVisible = true;
    pressKeyVisible = false;
    gameOverAndStageFase = 4;
  }
}

void nextLevelBonusCount()
{
  if (exitDoor.counter > 0)
  {
    exitDoor.counter--;
    scorePlayer += 5;
  }
  else
  {
    if (displayLevel < 64) gameOverAndStageFase++;
    else
    {
      gameState = STATE_GAME_OVER;
      gameOverAndStageFase = 0;
    }
  }
}

void nextLevelWait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 8)
  {
    gameOverAndStageFase++;
    globalCounter = 0;
  }
}

void nextLevelSlideToMiddle()
{
  bonusVisible = false;
  nextLevelVisible = true;
  if (leftX < 27)
  {
    leftX += 4;
    rightX -= 4;
  }
  else gameOverAndStageFase++;
}


void nextLevelEnd()
{
  if (arduboy.everyXFrames(30)) pressKeyVisible = !pressKeyVisible;
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_GAME_PLAYING;
    gameOverAndStageFase = 0;
    bonusVisible = false;
    nextLevelVisible = false;
    pressKeyVisible = false;
    leftX = -52;
    rightX = 164;

    coolGirl.x = readPlayerAndExitData(0);
    coolGirl.y = readPlayerAndExitData(1);
    setDoorPosition(readPlayerAndExitData(2), readPlayerAndExitData(3));

    for (byte i = 0; i < ((displayLevel - 1) / NUM_MAPS) + 2; i++)
    {
      addSurvivor(readSurvivorData(2 * i), readSurvivorData((2 * i) + 1));
    }
  }
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM nextLevelFases[] =
{
  nextLevelStart,
  nextLevelWait,
  nextLevelBonusCount,
  nextLevelWait,
  nextLevelSlideToMiddle,
  nextLevelWait,
  nextLevelEnd,
};

void stateGameNextLevel()
{
  ((FunctionPointer) pgm_read_word (&nextLevelFases[gameOverAndStageFase]))();
  if (bonusVisible)
  {
    sprites.drawSelfMasked(32, 16, bonusPoints, 0);
    drawNumbers(78, 16, FONT_SMALL, DATA_TIMER);
    drawNumbers(36, 36, FONT_BIG, DATA_SCORE);
  }
  if (nextLevelVisible)
  {
    sprites.drawSelfMasked(leftX, 24, nextLevel, 0);
    if (pressKeyVisible) sprites.drawSelfMasked(37, 48, pressKey, 0);
    drawNumbers(rightX, 24, FONT_BIG, DATA_LEVEL);
  }
}

// stateGameOver
// called each frame the gamestate is set to game over

void gameOverEnd()
{
  if (arduboy.everyXFrames(30)) pressKeyVisible = !pressKeyVisible;
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
    gameOverAndStageFase = 0;
    pressKeyVisible = false;
  }
}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM gameOverFases[] =
{
  nextLevelWait,
  gameOverEnd,
};

void stateGameOver()
{
  ((FunctionPointer) pgm_read_word (&gameOverFases[gameOverAndStageFase]))();
  sprites.drawSelfMasked(16, 8, gameOver, 0);
  drawNumbers(36, 32, FONT_BIG, DATA_SCORE);
  if (pressKeyVisible) sprites.drawSelfMasked(37, 56, pressKey, 0);
}

void stateGamePause()
{
  sprites.drawSelfMasked(30, 0, titleScreen02, 0);
  sprites.drawSelfMasked(92, 0, titleScreen03, 0);
  sprites.drawSelfMasked(37, 40, pause, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_GAME_PLAYING;
    sprites.drawSelfMasked(22, 32, gameOver, 0);
  }
}

void checkPause()
{
  if (arduboy.pressed(A_BUTTON + B_BUTTON)) gameState = STATE_GAME_PAUSE;
}

