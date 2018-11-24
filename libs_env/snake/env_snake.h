#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "env.h"

#include "snake.h"
#include "food.h"
#include <visualisation/glvisualisation.h>

class EnvSnake: public Env
{
  protected:
    float max_x, max_y;

    Snake           snake;
    Food            food;
    GLVisualisation visualisation;

  public:
    // Default constructor
    EnvSnake(unsigned int sensors_count = 32);

    // Copy constructor
    EnvSnake(EnvSnake& other);

    // Copy constructor
    EnvSnake(const EnvSnake& other);

    // Destructor
    virtual ~EnvSnake();

    // Copy assignment operator
    EnvSnake& operator= (EnvSnake& other);

    // Copy assignment operator
    EnvSnake& operator= (const EnvSnake& other);

  protected:
    void copy_snake(EnvSnake& other);
    void copy_snake(const EnvSnake& other);

  public:
    void action(unsigned int action_id);

    void render();

};


#endif
