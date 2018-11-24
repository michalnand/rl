#include "env_cliff.h"
#include <iostream>


EnvCliff::EnvCliff(unsigned int size)
              :Env()
{
  m_actions_count = 4;

  m_size = size;

  x_pos = 0;
  y_pos = 0;


  m_state.init(m_size, m_size, 1);


  rewards.resize(m_size);
  for (unsigned int j = 0; j < m_size; j++)
  {
    rewards[j].resize(m_size);
    for (unsigned int i = 0; i < m_size; i++)
      rewards[j][i] = 0.0;
  }

  for (unsigned int i = 1; i < (m_size-1); i++)
    rewards[0][i] =  -1.0;

  rewards[0][m_size-1] =  1.0;
}

EnvCliff::EnvCliff(EnvCliff& other)
              :Env(other)
{
  copy_cliff(other);
}

EnvCliff::EnvCliff(const EnvCliff& other)
              :Env(other)
{
  copy_cliff(other);
}

EnvCliff::~EnvCliff()
{

}

EnvCliff& EnvCliff::operator= (EnvCliff& other)
{
  copy(other);
  copy_cliff(other);

  return *this;
}

EnvCliff& EnvCliff::operator= (const EnvCliff& other)
{
  copy(other);
  copy_cliff(other);

  return *this;
}

void EnvCliff::copy_cliff(EnvCliff& other)
{
  rewards = other.rewards;
  x_pos   = other.x_pos;
  y_pos   = other.y_pos;
}

void EnvCliff::copy_cliff(const EnvCliff& other)
{
  rewards = other.rewards;
  x_pos   = other.x_pos;
  y_pos   = other.y_pos;
}

void EnvCliff::action(unsigned int action_id)
{
  switch(action_id)
  {
    case 0: x_pos = max(x_pos-1, 0);        break;
    case 1: x_pos = min(x_pos+1, m_size-1); break;
    case 2: y_pos = min(y_pos+1, m_size-1); break;
    case 3: y_pos = max(y_pos-1, 0);        break;
  }


  m_reward = rewards[y_pos][x_pos];
  m_done = false;

  if (m_reward > 0.0)
  {
    m_done  = true;
    x_pos   = 0;
    y_pos   = 0;
  }
  else
  if (m_reward < 0.0)
  {
    m_done  = true;
    x_pos   = 0;
    y_pos   = 0;
  }

  process_step();
  update_state();
}

void EnvCliff::print()
{
  for (int y = 0; y < (int)m_size; y++)
  {
    for (int x = 0; x < (int)m_size; x++)
    {
      if ((x == x_pos)&&(y == y_pos))
        std::cout << "*";
      else if (rewards[y][x] < 0.0)
        std::cout << "!";
      else if (rewards[y][x] > 0.0)
        std::cout << "T";
      else
        std::cout << ".";
      std::cout << " ";
    }

    std::cout << "\n";
  }

  std::cout << "\n";
}

void EnvCliff::render()
{
  visualisation.start();

  float r =0 , g = 0, b = 0;

  for (int y = 0; y < (int)m_size; y++)
  {
    for (int x = 0; x < (int)m_size; x++)
    {
      if ((x == x_pos)&&(y == y_pos))
      {
        r = 1.0;
        g = 1.0;
        b = 0.0;
      }
      else if (rewards[y][x] < 0.0)
      {
        r = 1.0;
        g = 0.0;
        b = 0.0;
      }
      else if (rewards[y][x] > 0.0)
      {
        r = 0.0;
        g = 1.0;
        b = 0.0;
      }
      else
      {
        r = 1.0;
        g = 1.0;
        b = 1.0;
      }

      visualisation.push();
      visualisation.translate(vpos(x), -vpos(y), -3.0);
      visualisation.set_color(r, g, b);
      visualisation.paint_square(1.8/m_size);
      visualisation.pop();
    }
  }

    std::string score;
    score = "score = " + std::to_string(m_score);
    visualisation.push();
    visualisation.set_color(1.0, 0.0, 0.0);
    visualisation.print(-0.2, -0.96, -3.0, score);
    visualisation.pop();

  visualisation.finish();
}


int EnvCliff::min(int a, int b)
{
  if (a < b)
    return a;
  return b;
}

int EnvCliff::max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}


float EnvCliff::vpos(float pos)
{
  float res = pos*1.0/m_size;
  return 2.0*(res - 0.5);
}



void EnvCliff::update_state()
{
  m_state.clear();

  m_state.set_element(1.0, x_pos, y_pos);

  if (m_done)
    m_state.set_terminal();
  else
    m_state.set_no_terminal();
}
