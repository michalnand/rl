#include "stack_item.h"

#include <stdio.h>
#include <stdlib.h>

StackItem::StackItem( unsigned int area_width, unsigned int area_height,
                      unsigned int width, unsigned int height)
{
  this->area_width = area_width;
  this->area_height = area_height;
  this->width = width;
  this->height = height;

  position = 0;

  move_type = 0;
  state = 5;

  x = (area_width - width)/2;
  y = (area_height - height)/2;
  target_x = x;
  target_y = y;

  values.resize(area_height);
  for (unsigned int j = 0; j < values.size(); j++)
  {
    values[j].resize(area_width);

    for (unsigned int i = 0; i < values[j].size(); i++)
      values[j][i] = 0.0;
  }

  other = nullptr;

  fill_values();
}

StackItem::StackItem(StackItem *other)
{
  this->other = other;


  this->area_width  = other->area_width;
  this->area_height = other->area_height;
  this->width  = other->width;
  this->height = other->height;


  move_type = other->move_type + 1;
  state = 2;

  position = 0;


  x = other->x;
  y = other->y;
  target_x = x;
  target_y = y;

  values.resize(area_height);
  for (unsigned int j = 0; j < values.size(); j++)
  {
    values[j].resize(area_width);

    for (unsigned int i = 0; i < values[j].size(); i++)
      values[j][i] = 0.0;
  }


  if ((move_type%2) ==0)
  {
    state = 0;
    x = rand()%(area_width - width);
  }
  else
  {
    state = 2;
    y = rand()%(area_width - width);
  }

  fill_values();
}


float StackItem::compute_overlap()
{
  float max_count = 0.0;
  float count = 0.0;
  for (unsigned int j = 0; j < values.size(); j++)
    for (unsigned int i = 0; i < values[j].size(); i++)
    {
      if (other->values[j][i] > 0.0)
        max_count+= 1.0;

      if (other->values[j][i] > 0.0)
      if (values[j][i] > 0.0)
        count+= 1.0;
    }

  return count/(max_count + 0.000000001);
}

void StackItem::process(unsigned int action)
{
  if (action == 1)
  {
    state = 4;
  }


  switch (state)
  {
    case 0:
            if (x < (area_width - width))
              x++;
            else
              state = 1;
            break;
    case 1:
            if (x > 0)
              x--;
            else
              state = 0;
            break;

    case 2:
            if (y < (area_height - height))
              y++;
            else
              state = 3;
            break;

    case 3:
            if (y > 0)
              y--;
            else
              state = 2;
            break;

    default:
            break;
  }

  fill_values();
}

void StackItem::print()
{
  for (unsigned int j = 0; j < values.size(); j++)
  {
    for (unsigned int i = 0; i < values[j].size(); i++)
    {
      if (values[j][i] > 0.0)
        printf("*");
      else
        printf(".");
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void StackItem::fill_values()
{
  for (int j = 0; j < (int)values.size(); j++)
    for (int i = 0; i < (int)values[j].size(); i++)
      values[j][i] = 0.0;


  for (int j = 0; j < height; j++)
    for (int i = 0; i < width; i++)
    {
      int y_ = j + y;
      int x_ = i + x;


      if ( y_ < area_height && x_ < area_width )
      {
        values[y_][x_] = 0.5;
        if ((j == 0)||(i == 0)||(j+1 == height)||(i+1 == width))
          values[y_][x_] = 1.0;
      }
    }
}
