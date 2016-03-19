#include "game.h"


// method implementations ////////////////////////////////////////////////////

// stateGamePlaying
// called each frame the gamestate is set to playing
void stateGamePlaying()
{
  // Update Level
  if(!(arduboy.frameCount % (60*3))) {
    addZombie(128, 128);
  }
  
  
  // Update Objects
  updatePlayer(coolGirl);
  updateBullets();
  updateZombies();
  updateSurvivors();
  
  // Draw
  drawLevel();
  drawSurvivors();
  drawZombies();
  drawBullets();
  drawPlayer(coolGirl);
  drawWeapons();
}

// stateGameNextLevel
// called each frame the gamestate is set to next level
void stateGameNextLevel()
{
  clearSurvivors();
  clearZombies();
  clearWeapons();
  
  addZombie(128, 128);
  addSurvivor(64+16, 48);
  addWeapon(128, 16, 1);

  gameState = STATE_GAME_PLAYING;
}

// stateGamePause
// called each frame the gamestate is set to paused
void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
  }
}

// stateGameOver
// called each frame the gamestate is set to game over
void stateGameOver()
{
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
  }
}
