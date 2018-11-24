#include "snake.h"

#include <math.h>


Snake::Snake()
{
  m_speed_right = 0.0;
  m_speed_left  = 0.0;
  m_theta       = 0.0;

  elements.resize(10);
}

Snake::Snake(Snake& other)
{
  copy(other);
}

Snake::Snake(const Snake& other)
{
  copy(other);
}

Snake::~Snake()
{

}

Snake& Snake::operator= (Snake& other)
{
  copy(other);

  return *this;
}

Snake& Snake::operator= (const Snake& other)
{
  copy(other);

  return *this;
}

void Snake::copy(Snake& other)
{
  m_x     = other.m_x;
  m_y     = other.m_y;
  m_theta = other.m_theta;

  m_speed_left = other.m_speed_left;
  m_speed_right = other.m_speed_right;
}

void Snake::copy(const Snake& other)
{
  m_x     = other.m_x;
  m_y     = other.m_y;
  m_theta = other.m_theta;

  m_speed_left = other.m_speed_left;
  m_speed_right = other.m_speed_right;
}










void Snake::init(GLVisualisation &visualisation)
{
  this->visualisation = &visualisation;

  respawn();
}

void Snake::forward()
{
  m_speed_right = 1.0;
  m_speed_left  = 1.0;

  process_move();
}

void Snake::left()
{
  m_speed_right =  1.0;
  m_speed_left  =  0.3;

  process_move();
}

void Snake::right()
{
  m_speed_right = 0.3;
  m_speed_left  = 1.0;

  process_move();
}

void Snake::respawn()
{
  m_x = rnd()*0.1;
  m_y = rnd()*0.1;

  m_speed_right = 0.0;
  m_speed_left  = 0.0;
  m_theta = 0.0;
}


void Snake::render()
{
  for (unsigned int i = 0; i < elements.size(); i++)
  {
    visualisation->push();
    visualisation->set_color(0.0, 1.0, 0.0);

    // visualisation->rotate(0.0, 0.0, -m_theta*360.0/3.141592654);
    visualisation->translate(elements[i].x, elements[i].y, -3.0);

    visualisation->paint_square(0.05);

    visualisation->pop();
  }
}


float Snake::rnd()
{
  float v = (rand()%1000000)/1000000.0;
  if (rand()%2)
    v*= -1.0;

  return v;
}


void Snake::process_move()
{
  float dt = 0.05;
  float PI = 3.141592654;

  //speed to position change in polar coordinates
  float d_dist  = dt*(m_speed_left + m_speed_right)/2.0;
  float d_theta = dt*(m_speed_left - m_speed_right)*16.0;

  m_theta+= d_theta;
  m_theta = fmod(m_theta, 2.0*PI);

  //polar coordinates to cartesian plague
  m_x+= d_dist*cos(m_theta);
  m_y+= d_dist*sin(m_theta);


  for (unsigned int i = 0; i < elements.size()-1; i++)
    elements[i] = elements[i+1];

  elements[elements.size()-1].x = m_x;
  elements[elements.size()-1].y = m_y;
}
