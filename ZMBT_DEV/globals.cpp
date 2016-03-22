#include "globals.h"

// globals ///////////////////////////////////////////////////////////////////

Arduboy arduboy;
Sprites sprites(arduboy);
SimpleButtons buttons(arduboy);
unsigned long scorePlayer;
boolean soundYesNo;
byte gameState;

// function implementations //////////////////////////////////////////////////

short converge(short start, short goal, short step)
{
  if(start < goal)
  {
    start += step;
    if(start > goal) return goal;
  }
  else if(start > goal)
  {
    start -= step;
    if(start < goal) return goal;
  }
  
  return start;
}
