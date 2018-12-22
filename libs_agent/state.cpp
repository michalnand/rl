#include "state.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <iomanip>

State::State()
{
  m_w     = 0;
  m_h     = 0;
  m_d     = 0;
  m_size  = 0;
  m_terminal = false;
}

State::State(State& other)
{
  copy(other);
}

State::State(const State& other)
{
  copy(other);
}

State::State(unsigned int w, unsigned int h, unsigned int d)
{
  init(w, h, d);
}

State::~State()
{

}

State& State::operator= (State& other)
{
  copy(other);
  return *this;
}

State& State::operator= (const State& other)
{
  copy(other);
  return *this;
}

void State::init(unsigned int w, unsigned h, unsigned d)
{
  m_w = w;
  m_h = h;
  m_d = d;
  m_terminal = false;

  m_size = m_w*m_h*m_d;
  m_state.resize(m_size);

  for (unsigned int i = 0; i < m_state.size(); i++)
    m_state[i] = 0.0;
}


void State::copy(State& other)
{
  m_w = other.m_w;
  m_h = other.m_h;
  m_d = other.m_d;

  m_state = other.m_state;
  m_terminal = other.m_terminal;

  m_size = m_w*m_h*m_d;


}

void State::copy(const State& other)
{
  m_w = other.m_w;
  m_h = other.m_h;
  m_d = other.m_d;

  m_state = other.m_state;
  m_terminal = other.m_terminal;

  m_size = m_w*m_h*m_d;
}

std::vector<float>& State::get()
{
  return m_state;
}

void State::set(std::vector<float> &state)
{
  for (unsigned int i = 0; i < m_state.size(); i++)
    m_state[i] = state[i];
}

void State::set_element(float value, unsigned int w, unsigned int h, unsigned int d)
{
  unsigned int idx = (d*m_h + h)*m_w + w;
  m_state[idx] = value;
}

float State::get_element(unsigned int w, unsigned int h, unsigned int d)
{
  unsigned int idx = (d*m_h + h)*m_w + w;
  return m_state[idx];
}

void State::clear()
{
  for (unsigned int i = 0; i < m_state.size(); i++)
    m_state[i] = 0.0;
}

bool State::is_terminal()
{
  return m_terminal;
}

void State::set_terminal()
{
  m_terminal = true;
}

void State::set_no_terminal()
{
  m_terminal = false;
}


std::string State::as_string(unsigned int precision)
{
  std::stringstream s_stream;

  s_stream.precision(precision);

  unsigned int ptr = 0;

  for (unsigned int d_ = 0; d_ < d(); d_++)
  {
    for (unsigned int h_ = 0; h_ < h(); h_++)
    {
      for (unsigned int w_ = 0; w_ < w(); w_++)
      {
        s_stream << std::setw(5) << m_state[ptr] << " ";
        ptr++;
      }

      s_stream << "\n";
    }

    s_stream << "\n";
  }

  s_stream << "\n";

  return s_stream.str();
}

void State::print(unsigned int precision)
{
  std::cout << as_string(precision);
}


bool State::is_valid()
{
  for (unsigned int i = 0; i < m_state.size(); i++)
    if (isnan(m_state[i]))
      return false;

  for (unsigned int i = 0; i < m_state.size(); i++)
    if (isinf(m_state[i]))
      return false;

  return true;
}

void State::random(float range)
{
  for (unsigned int i = 0; i < m_state.size(); i++)
    m_state[i] = range*randf();
}

void State::add_noise(float level)
{
  for (unsigned int i = 0; i < m_state.size(); i++)
    m_state[i] = (1.0 - level)*m_state[i] + level*randf();
}

float State::randf()
{
  return ((rand()%2000000)/1000000.0) - 1.0;
}


unsigned int State::argmax()
{
  unsigned int max_idx  = 0;
  float max             = m_state[max_idx];

  for (unsigned int i = 0; i < m_state.size(); i++)
    if (max < m_state[i])
    {
      max     = m_state[i];
      max_idx = i;
    }

  return max_idx;
}

unsigned int State::argmin()
{
  unsigned int min_idx  = 0;
  float min             = m_state[min_idx];

  for (unsigned int i = 0; i < m_state.size(); i++)
    if (min > m_state[i])
    {
      min     = m_state[i];
      min_idx = i;
    }

  return min_idx;
}

float State::dot(State& other)
{
  float result = 0.0;

  for (unsigned int i = 0; i < m_state.size(); i++)
    result+= m_state[i]*other.m_state[i];

  return result;
}

float State::distance(State& other)
{
  float result = 0.0;

  for (unsigned int i = 0; i < m_state.size(); i++)
  {
    float tmp = m_state[i] - other.m_state[i];
    result+= tmp*tmp;
  }
  return sqrt(result);
}


void State::normalise()
{
  float max_value = fabs(m_state[argmax()]);
  float min_value = fabs(m_state[argmin()]);

  float value;

  if (max_value > min_value)
    value = max_value;
  else
    value = min_value;

  if (value > 0)
  {
    for (unsigned int i = 0; i < m_state.size(); i++)
      m_state[i]/= value;
  }
}
