#include "env_pong.h"

#include <iostream>


EnvPong::EnvPong(unsigned int size)
              :Env()
{
  m_actions_count = 3;

  this->size = size;

  reset();

  m_state.init(size, size, 3);
}

EnvPong::EnvPong(EnvPong& other)
              :Env(other)
{
  copy_pong(other);
}

EnvPong::EnvPong(const EnvPong& other)
              :Env(other)
{
  copy_pong(other);
}

EnvPong::~EnvPong()
{

}

EnvPong& EnvPong::operator= (EnvPong& other)
{
  copy(other);
  copy_pong(other);

  return *this;
}

EnvPong& EnvPong::operator= (const EnvPong& other)
{
  copy(other);
  copy_pong(other);

  return *this;
}

void EnvPong::copy_pong(EnvPong& other)
{
  size = other.size;
  player_size = other.player_size;

  ball_x = other.ball_x;
  ball_y = other.ball_y;

  ball_dx = other.ball_dx;
  ball_dy = other.ball_dy;

  player_a = other.player_a;
  player_b = other.player_b;
}

void EnvPong::copy_pong(const EnvPong& other)
{
  size = other.size;
  player_size = other.player_size;

  ball_x = other.ball_x;
  ball_y = other.ball_y;

  ball_dx = other.ball_dx;
  ball_dy = other.ball_dy;

  player_a = other.player_a;
  player_b = other.player_b;
}

void EnvPong::action(unsigned int action_id)
{

/*
  if (player_a > ball_y)
    player_a--;
  else
    player_a++;
*/

  switch(action_id)
  {
    case 0: break;
    case 1: player_a = min(player_a + 1, size - player_size/2); break;
    case 2: player_a = max(player_a - 1, player_size/2); break;
  }

  if (player_b > ball_y)
    player_b--;
  else
    player_b++;


  m_reward = 0.0;

  if (ball_y <= 0)
  {
    ball_dy = 1;
  }
  else
  if (ball_y >= size-1)
  {
    ball_dy = -1;
  }
  else
  if ((ball_x == 1)&&(abs(ball_y - player_a) < player_size/2))
  {
    ball_dx = 1;
    m_reward = 1.0;
  }
  else
  if ((ball_x == size-2)&&(abs(ball_y - player_b) < player_size/2))
  {
    ball_dx = -1;
  }

  ball_x+= ball_dx;
  ball_y+= ball_dy;

  if (ball_x > (size-1) )
  {
    m_reward = 1.0;
    reset();
  }
  else
  if (ball_x <= 0 )
  {
    m_reward = -1.0;
    reset();
  }

  process_step();
  update_state();
}

void EnvPong::print()
{
  std::cout << "score = " << m_score << "\n";
}

void EnvPong::render()
{
  visualisation.start();

  visualisation.push();
  visualisation.translate(vpos(ball_x), vpos(ball_y), -3.0);
  visualisation.set_color(1.0, 1.0, 1.0);
  visualisation.paint_circle(1.0/size);
  visualisation.pop();

  for (int i = 0; i < player_size; i++)
  {
    visualisation.push();
    visualisation.translate(vpos(1), vpos(player_a + i - player_size/2), -3.0);
    visualisation.set_color(0.0, 0.0, 1.0);
    visualisation.paint_square(2.0/size);
    visualisation.pop();
  }

  for (int i = 0; i < player_size; i++)
  {
    visualisation.push();
    visualisation.translate(vpos(size-2), vpos(player_b + i - player_size/2), -3.0);
    visualisation.set_color(1.0, 0.0, 0.0);
    visualisation.paint_square(2.0/size);
    visualisation.pop();
  }


  visualisation.finish();
}


void EnvPong::reset()
{
  this->player_size = 5;

  this->ball_x = size/2;
  this->ball_y = rand()%(size/4) + size/2;

  if (rand()%2)
    this->ball_dx = 1;
  else
    this->ball_dx = -1;

  if (rand()%2)
    this->ball_dy = 1;
  else
    this->ball_dy = -1;


  this->player_a = size/2;
  this->player_b = size/2;
}

void EnvPong::update_state()
{
  m_state.clear();


  m_state.set_element(1.0, ball_x, ball_y, 0);
  m_state.set_element(1.0, 1, player_a, 1);
  m_state.set_element(1.0, size-2, player_b, 2);
}



int EnvPong::min(int a, int b)
{
  if (a < b)
    return a;
  return b;
}

int EnvPong::max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}

float EnvPong::vpos(float pos)
{
  return 2.0*((pos*1.0/size) - 0.5);
}
