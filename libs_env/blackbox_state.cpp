#include "blackbox_state.h"
#include <stdlib.h>

#include <stdio.h>
#include <image_save.h>

BlackBoxState::BlackBoxState()
{
  m_state_size = 0;
  m_reward = 0;
  m_x = 0;
  m_y = 0;

  m_max = 0;
  m_min = 0;
}


BlackBoxState::BlackBoxState(   unsigned int state_size,
                                unsigned int transitions_count,
                                unsigned int area_size,
                                float x,
                                float y,
                                PerlinNoise &noise)
{
  m_reward = rnd();

  m_x = x;
  m_y = y;

  this->m_state_size = state_size;
  m_state.resize(m_state_size*m_state_size);
  m_transition.resize(transitions_count);


  unsigned int ptr = 0;

  for (unsigned int y = 0; y < m_state_size; y++)
    for (unsigned int x = 0; x < m_state_size; x++)
    {
      float x_ = (m_x + x - m_state_size/2.0)*1.0/area_size;
      float y_ = (m_y + y - m_state_size/2.0)*1.0/area_size;

      m_state[ptr] = noise.get(10.0*x_, 10.0*y_);
      ptr++;
    }


  m_max = m_state[0];
  m_min = m_max;

  for (unsigned int i = 0; i < m_state.size(); i++)
  {
    if (m_state[i] > m_max)
      m_max = m_state[i];
    if (m_state[i] < m_min)
      m_min = m_state[i];
  }
}

BlackBoxState::BlackBoxState(BlackBoxState& other)
{
  copy(other);
}

BlackBoxState::BlackBoxState(const BlackBoxState& other)
{
  copy(other);
}

BlackBoxState::~BlackBoxState()
{

}

BlackBoxState& BlackBoxState::operator= (BlackBoxState& other)
{
  copy(other);

  return *this;
}

BlackBoxState& BlackBoxState::operator= (const BlackBoxState& other)
{
  copy(other);

  return *this;
}

void BlackBoxState::copy(BlackBoxState& other)
{
  m_state_size = other.m_state_size;
  m_reward = other.m_reward;
  m_x = other.m_x;
  m_y = other.m_y;

  m_state = other.m_state;
  m_transition = other.m_transition;
}

void BlackBoxState::copy(const BlackBoxState& other)
{
  m_state_size = other.m_state_size;
  m_reward = other.m_reward;
  m_x = other.m_x;
  m_y = other.m_y;

  m_state = other.m_state;
  m_transition = other.m_transition;
}


float BlackBoxState::rnd()
{
  float res = (rand()%10000)/10000.0;
  if (rand()%2)
    res = -res;
  return res;
}


void BlackBoxState::normalise(float min, float max)
{
  float k = 0.0;
  float q = 0.0;

  if (max > min)
  {
    k = (1.0)/(max - min);
    q = 1.0 - k*max;
  }

  for (unsigned int i = 0; i < m_state.size(); i++)
    m_state[i] = k*m_state[i] + q;
}

void BlackBoxState::create_reward()
{
  float average = 0.0;
  for (unsigned int i = 0; i < m_state.size(); i++)
    average+= m_state[i];
  average/= m_state.size();

  unsigned int above = 0;
  unsigned int below = 0;

  float non_zero_ratio = 0.2;

  for (unsigned int i = 0; i < m_state.size(); i++)
  {
    if (m_state[i] > average)
      above++;

    if (m_state[i] < average)
      below++;
  }

  m_reward = 0;

  if (fabs(rnd()) < non_zero_ratio)
  {
    if (above > below)
      m_reward = 1.0;
    else
      m_reward = -1.0;
  }
}

void BlackBoxState::save_image_state(std::string file_name)
{
  ImageSave image(m_state_size, m_state_size, true);
  image.save(file_name, m_state);
}
