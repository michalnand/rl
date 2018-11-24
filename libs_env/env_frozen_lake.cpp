#include "env_frozen_lake.h"
#include <iostream>


EnvFrozenLake::EnvFrozenLake()
              :Env()
{
  m_actions_count = 4;

  m_size = 4;

  x_pos = 0;
  y_pos = 0;

  m_done = false;

  m_state.init(m_size, m_size, 1);


  rewards.resize(m_size);
  for (unsigned int j = 0; j < m_size; j++)
  {
    rewards[j].resize(m_size);
    for (unsigned int i = 0; i < m_size; i++)
      rewards[j][i] = 0.0;
  }

  rewards[1][1] =  -1.0;
  rewards[1][3] =  -1.0;
  rewards[2][3] =  -1.0;
  rewards[3][0] =  -1.0;
  rewards[3][3] =   1.0;
}

EnvFrozenLake::EnvFrozenLake(EnvFrozenLake& other)
              :Env(other)
{
  copy_frozen_lake(other);
}

EnvFrozenLake::EnvFrozenLake(const EnvFrozenLake& other)
              :Env(other)
{
  copy_frozen_lake(other);
}

EnvFrozenLake::~EnvFrozenLake()
{

}

EnvFrozenLake& EnvFrozenLake::operator= (EnvFrozenLake& other)
{
  copy(other);
  copy_frozen_lake(other);

  return *this;
}

EnvFrozenLake& EnvFrozenLake::operator= (const EnvFrozenLake& other)
{
  copy(other);
  copy_frozen_lake(other);

  return *this;
}

void EnvFrozenLake::copy_frozen_lake(EnvFrozenLake& other)
{
  rewards = other.rewards;
  x_pos   = other.x_pos;
  y_pos   = other.y_pos;
}

void EnvFrozenLake::copy_frozen_lake(const EnvFrozenLake& other)
{
  rewards = other.rewards;
  x_pos   = other.x_pos;
  y_pos   = other.y_pos;
}

void EnvFrozenLake::action(unsigned int action_id)
{
  switch((action_id + 14)%4)
  {
    case 0: x_pos = min(x_pos+1, m_size-1); break;
    case 1: x_pos = max(x_pos-1, 0);        break;
    case 2: y_pos = min(y_pos+1, m_size-1); break;
    case 3: y_pos = max(y_pos-1, 0);        break;
  }

  m_reward = rewards[y_pos][x_pos];

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
  else
    m_done = false;

  process_step();
  update_state();
}

void EnvFrozenLake::print()
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


int EnvFrozenLake::min(int a, int b)
{
  if (a < b)
    return a;
  return b;
}

int EnvFrozenLake::max(int a, int b)
{
  if (a > b)
    return a;
  return b;
}




void EnvFrozenLake::update_state()
{
  m_state.clear();

  m_state.set_element(1.0, x_pos, y_pos);

  if (m_done)
    m_state.set_terminal();
  else
    m_state.set_no_terminal();
}
