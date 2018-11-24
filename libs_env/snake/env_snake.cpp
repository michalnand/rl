#include "env_snake.h"
#include <iostream>
#include <math.h>


EnvSnake::EnvSnake(unsigned int sensors_count)
              :Env()
{
  max_x = 1.2;
  max_y = 1.2;

  snake.init(visualisation);
  food.init(sensors_count, visualisation);

  m_actions_count = 3;

  m_state.init(sensors_count, 1, 1);
  auto tmp = food.state(0.0, 0.0, 0.0);
  m_state.set(tmp);
}

EnvSnake::EnvSnake(EnvSnake& other)
              :Env(other)
{
  copy_snake(other);
}

EnvSnake::EnvSnake(const EnvSnake& other)
              :Env(other)
{
  copy_snake(other);
}

EnvSnake::~EnvSnake()
{

}

EnvSnake& EnvSnake::operator= (EnvSnake& other)
{
  copy(other);
  copy_snake(other);

  return *this;
}

EnvSnake& EnvSnake::operator= (const EnvSnake& other)
{
  copy(other);
  copy_snake(other);

  return *this;
}

void EnvSnake::copy_snake(EnvSnake& other)
{
  //visualisation = other.visualisation;
  snake         = other.snake;
  food          = other.food;
}

void EnvSnake::copy_snake(const EnvSnake& other)
{
  //visualisation = other.visualisation;
  snake         = other.snake;
  food          = other.food;
}


void EnvSnake::action(unsigned int action_id)
{
  switch(action_id)
  {
    case 0: snake.forward();  break;
    case 1: snake.left();     break;
    case 2: snake.right();    break;
  }

  m_reward = 0.0;

  m_done  = false;

  if ( (fabs(snake.x()) > max_x) || (fabs(snake.y()) > max_y) )
  {
    snake.respawn();
    m_reward = -1.0;

    m_done  = true;
  }

  if (food.eat(snake.x(), snake.y()) > 0.0)
  {
    m_reward = 0.1;

    m_done  = true;
  } 



  auto tmp = food.state(snake.x(), snake.y(), snake.theta());

  m_state.set(tmp);

  process_step();

}

void EnvSnake::render()
{
  visualisation.start();

  snake.render();
  food.render();


  std::string score;
  score = "score = " + std::to_string(m_score);
  visualisation.push();
  visualisation.set_color(1.0, 1.0, 1.0);
  visualisation.print(-0.2, 0.9, -3.0, score);
  visualisation.pop();

  visualisation.finish();
}
