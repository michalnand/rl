#include "env.h"

#include <thread>
#include <chrono>


Env::Env()
{
  m_actions_count = 0;
  m_reward        = 0;
  m_score         = 0;
  m_done          = false;

  m_epoch         = 0;
  m_iteration     = 0;

  unsigned int seed = (unsigned long int)this;
  srand(time(NULL) + seed);
}

Env::Env(Env& other)
{
  copy(other);
}

Env::Env(std::string path)
{
  load(path);
}

Env::Env(const Env& other)
{
  copy(other);
}

Env::~Env()
{

}

Env& Env::operator= (Env& other)
{
  copy(other);
  return *this;
}

Env& Env::operator= (const Env& other)
{
  copy(other);
  return *this;
}

void Env::copy(Env &other)
{
  m_state         = other.m_state;
  m_actions_count = other.m_actions_count;
  m_reward        = other.m_reward;
  m_score         = other.m_score;
  m_done          = other.m_done;
}

void Env::copy(const Env &other)
{
  m_state         = other.m_state;
  m_actions_count = other.m_actions_count;
  m_reward        = other.m_reward;
  m_score         = other.m_score;
  m_done          = other.m_done;
}

void Env::action(unsigned int action_id)
{
  (void)action_id;
}

void Env::load(std::string path)
{
  (void)path;
}

void Env::save(std::string path)
{
  (void)path;
}

void Env::print()
{

}

void Env::render()
{

}

void Env::monitor()
{

}

void Env::delay_ms(unsigned long int ms_time)
{
  std::this_thread::sleep_for (std::chrono::milliseconds(ms_time));
}

void Env::process_step()
{
  m_iteration++;
  m_score+= m_reward;
}
