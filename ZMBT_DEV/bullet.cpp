#include "bullet.h"
#include "player.h"

// globals ///////////////////////////////////////////////////////////////////
const char BulletXVelocities[8] = {
  0,
  -2,
  -3,
  -2,
  0,
  2,
  3,
  2,
};

Bullet bullets[BULLET_MAX];

// method implementations ////////////////////////////////////////////////////

// setBullet
// sets the position and the velocity of a bullet
void setBullet(Bullet& obj, int x, int y, int vx, int vy)
{
  obj.x = x;
  obj.y = y;
  obj.vx = vx;
  obj.vy = vy;
  obj.active = true;
}

// addBullet
// searches the bullet list for an empty slot, adds one if available
void addBullet(int x, int y, byte direction, int vx, int vy)
{
  byte id;
  
  for(id=0; id<BULLET_MAX; id++)
  {
    if(!bullets[id].active)
    {
      setBullet(
        bullets[id],
        x - BULLET_WIDTH/2,
        y - BULLET_HEIGHT/2,
        vx + BulletXVelocities[direction],
        vy + BulletXVelocities[(direction+6)%8]
      );
      arduboy.tunes.tone(440, 20);
      break;
    }
  }
}


// updateBullet
// updates a bullet according to the game rules
void updateBullet(Bullet& obj)
{
  byte id;
  
  // horizontal physics
  obj.x += obj.vx;
  
  // vertical physics
  obj.y += obj.vy;
  
  // collide with zombies
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(zombieCollision(zombies[id], obj.x, obj.y, BULLET_WIDTH, BULLET_HEIGHT))
    {
      obj.active = false;
      zombieHealthOffset(zombies[id], -1);
      break;
    }
  }
  
  // delete if gone off screen
  if((obj.x < mapPositionX) || (obj.y < mapPositionY) || (obj.x > WIDTH + mapPositionX) || (obj.y > HEIGHT + mapPositionY))
  {
    obj.active = false;
  }
}


// updateBullets
// updates the entire list of bullets
void updateBullets()
{
  byte id;
  
  for(id=0; id<BULLET_MAX; id++)
  {
    if(!bullets[id].active) continue;
    updateBullet(bullets[id]);
  }
}


// drawBullets
// draws the entire list of bullets
void drawBullets()
{
  byte id;
  int x, y;
  
  for(id=0; id<BULLET_MAX; id++)
  {
    if(!bullets[id].active) continue;
    x = bullets[id].x - mapPositionX;
    y = bullets[id].y - mapPositionY;
    if((x>0) && (y>0) && (x<WIDTH) && (y<HEIGHT))
    {
      arduboy.drawPixel(x, y, 1);
      arduboy.drawPixel(x+1, y, 1);
      arduboy.drawPixel(x, y+1, 1);
      arduboy.drawPixel(x+1, y+1, 1);
    }
  }
}


// clearBullets
// clears the entire list of bullets
void clearBullets()
{
  byte id;
  
  for(id=0; id<BULLET_MAX; id++)
  {
    bullets[id].active = false;
  }
}
