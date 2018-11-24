#ifndef _SNAKE_BOT_H_
#define _SNAKE_BOT_H_

#include <state.h>
#include <visualisation/glvisualisation.h>

#include "food.h"

struct sSnakePoint
{
  float x, y;
};

class Snake
{
  protected:
    GLVisualisation *visualisation;

    float m_speed_right, m_speed_left, m_theta;

    float m_x, m_y;

    std::vector<sSnakePoint> elements;

  public:
    // Default constructor
    Snake();

    // Copy constructor
    Snake(Snake& other);

    // Copy constructor
    Snake(const Snake& other);

    // Destructor
    virtual ~Snake();

    // Copy assignment operator
    Snake& operator= (Snake& other);

    // Copy assignment operator
    Snake& operator= (const Snake& other);

  protected:
    void copy(Snake& other);
    void copy(const Snake& other);

  public:
    void init(GLVisualisation &visualisation);

    void forward();
    void left();
    void right();

    void respawn();

    void render();

  public:
    float x()
    {
      return m_x;
    }

    float y()
    {
      return m_y;
    }

    float theta()
    {
      return m_theta;
    }


  private:
    void process_move();
    float rnd();



};


#endif
