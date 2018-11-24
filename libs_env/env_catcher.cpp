#include "env_catcher.h"

#include <iostream>

 
EnvCatcher::EnvCatcher(unsigned int size)
              :Env()
{
  m_actions_count = 3;

  this->size  = size;
  this->target_size = 2;

  this->target_position_y = this->size-2;
  this->target_position_x = this->size/2;

  this->agent_position    = this->size/2;
  this->agent_size        = target_size*2;

  m_state.init(this->size, this->size, 1);
}

EnvCatcher::EnvCatcher(EnvCatcher& other)
              :Env(other)
{
  copy_catcher(other);
}

EnvCatcher::EnvCatcher(const EnvCatcher& other)
              :Env(other)
{
  copy_catcher(other);
}

EnvCatcher::~EnvCatcher()
{

}

EnvCatcher& EnvCatcher::operator= (EnvCatcher& other)
{
  copy(other);
  copy_catcher(other);

  return *this;
}

EnvCatcher& EnvCatcher::operator= (const EnvCatcher& other)
{
  copy(other);
  copy_catcher(other);

  return *this;
}

void EnvCatcher::copy_catcher(EnvCatcher& other)
{
  size              = other.size;
  target_size       = other.target_size;
  target_position_y = other.target_position_y;
  target_position_x = other.target_position_x;
  agent_position    = other.agent_position;
  agent_size        = other.agent_size;
}

void EnvCatcher::copy_catcher(const EnvCatcher& other)
{
  size              = other.size;
  target_size       = other.target_size;
  target_position_y = other.target_position_y;
  target_position_x = other.target_position_x;
  agent_position    = other.agent_position;
  agent_size        = other.agent_size;
}


void EnvCatcher::action(unsigned int action_id)
{
  target_position_y--;


  switch(action_id)
  {
    case 0: break;
    case 1: agent_position = min(agent_position + 1, size - agent_size/2); break;
    case 2: agent_position = max(agent_position - 1, agent_size/2); break;
  }

  m_reward = 0.0;

  m_done = false;

  if (target_position_y <= 0)
  {
    int distance = abs(agent_position - target_position_x);

    if (distance < agent_size)
    {
      m_reward = 0.5;
      m_done = true;
    }
    else
    {
      m_reward = -1.0;
      m_done = true;
    }


    target_position_y = size-target_size;
    target_position_x = rand()%(size - target_size);
  }


  process_step();
  update_state();
}

void EnvCatcher::print()
{
  std::cout << "score = " << m_score << "\n";
//  m_state.print();
}

void EnvCatcher::render()
{
  visualisation.start();

  float element_size = 1.8/size;

  for (int y = 0; y < size; y++)
  for (int x = 0; x < size; x++)
  {
    visualisation.push();
    visualisation.translate(vpos(x), vpos(y), -3.0);
    visualisation.set_color(0.3, 0.3, 0.3);
    visualisation.paint_square(element_size);
    visualisation.pop();
  }

  for (int y = 0; y < target_size; y++)
  for (int x = 0; x < target_size; x++)
  {
    visualisation.push();
    visualisation.translate(vpos(target_position_x + x), vpos(target_position_y + y), -3.0);
    visualisation.set_color(1.0, 0.0, 0.0);
    visualisation.paint_square(element_size);
    visualisation.pop();
  }

  for (int x = 0; x < agent_size; x++)
  {
    visualisation.push();
    visualisation.translate(vpos(agent_position + x - agent_size/2.0), vpos(0), -3.0);
    visualisation.set_color(1.0, 1.0, 1.0);
    visualisation.paint_square(element_size);
    visualisation.pop();
  }


  std::string score;
  score = "score = " + std::to_string(m_score);
  visualisation.push();
  visualisation.set_color(1.0, 1.0, 1.0);
  visualisation.print(-0.2, 0.9, -3.0, score);
  visualisation.pop();


  visualisation.finish();
}

void EnvCatcher::update_state()
{
  m_state.clear();

  for (int y = 0; y < target_size; y++)
  for (int x = 0; x < target_size; x++)
  {
    unsigned int x_ = x + target_position_x;
    unsigned int y_ = y + target_position_y;

    m_state.set_element(1.0, x_, y_, 0);
  }

  for (int x = 0; x < agent_size; x++)
    m_state.set_element(1.0, x - agent_size/2 + agent_position, 0, 0);

/*
  if (m_done)
    m_state.set_terminal();
  else
    m_state.set_no_terminal();
  */
}



int EnvCatcher::min(int a, int b)
{
  if (a < b)
    return a;
  return b;
}

int EnvCatcher::max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}

float EnvCatcher::vpos(float pos)
{
  return 2.0*((pos*1.0/size) - 0.5);
}
