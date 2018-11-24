#include "arcade_obstacle.h"



ArcadeObstacle::ArcadeObstacle()
{
  x = 0;
  y = 0;
  field_type = AF_COMMON;
}

ArcadeObstacle::~ArcadeObstacle()
{

}

void ArcadeObstacle::create(unsigned int x, unsigned int y, unsigned int max_width, unsigned int max_height, AracadeField field)
{
  this->x = x;
  this->y = y;
  this->field_type = field;

  if (obstacle.size() != max_height)
    obstacle.resize(max_width);

  if (obstacle[0].size() != max_width)
  {
    for (unsigned int j = 0; j < obstacle.size(); j++)
      obstacle[j].resize(max_width);
  }

  for (unsigned int j = 0; j < obstacle.size(); j++)
    for (unsigned int i = 0; i < obstacle[j].size(); i++)
      obstacle[j][i] = AF_EMPTY;

  for (unsigned int j = 0; j < obstacle.size(); j++)
    for (unsigned int i = 0; i < obstacle[j].size(); i++)
      if ((rand()%100) < 50)
        obstacle[j][i] = field_type;
}

void ArcadeObstacle::add_to_screen(ArcadeScreen &screen)
{
  for (unsigned int j = 0; j < obstacle.size(); j++)
    for (unsigned int i = 0; i < obstacle[j].size(); i++)
      if (obstacle[j][i] != AF_EMPTY)
      {
        int x_ = x + (int)i;
        int y_ = y + (int)j;
        if ( (y_ >= 0) && (y_ < (int)screen.height()) )
        if ( (x_ >= 0) && (x_ < (int)screen.width()) )
          screen.set(x_, y_, obstacle[j][i]);
      }
}

bool ArcadeObstacle::is_out(ArcadeScreen &screen)
{
  unsigned int in_count = 0;
  for (unsigned int j = 0; j < obstacle.size(); j++)
    for (unsigned int i = 0; i < obstacle[j].size(); i++)
      {
        int x_ = x + (int)i;
        int y_ = y + (int)j;
        if ( (y_ >= 0) && (y_ < (int)screen.height()) )
        if ( (x_ >= 0) && (x_ < (int)screen.width()) )
          in_count++;
      }

  if (in_count == 0)
    return true;

  return false;
}

bool ArcadeObstacle::is_colission(unsigned int pos_x, unsigned int pos_y)
{
  for (unsigned int j = 0; j < obstacle.size(); j++)
    for (unsigned int i = 0; i < obstacle[j].size(); i++)
      if (obstacle[j][i] != AF_EMPTY)
      {
        int x_ = x + (int)i;
        int y_ = y + (int)j;

        if ( (x_ == (int)pos_x) && (y_ == (int)pos_y) )
          return true;
      }

  return false;
}

void ArcadeObstacle::move(int dx, int dy)
{
  x+= dx;
  y+= dy;
}

AracadeField ArcadeObstacle::get_type()
{
  return field_type;
}
