#ifndef _BLACK_BOX_STATE_H_
#define _BLACK_BOX_STATE_H_

#include <vector>
#include <string>
#include "perlin_noise.h"

class BlackBoxState
{
  public:
    // Default constructor
    BlackBoxState();

    BlackBoxState(  unsigned int state_size,
                    unsigned int transitions_count,
                    unsigned int area_size,
                    float x,
                    float y,
                    PerlinNoise &noise);

    // Copy constructor
    BlackBoxState(BlackBoxState& other);

    // Copy constructor
    BlackBoxState(const BlackBoxState& other);

    // Destructor
    virtual ~BlackBoxState();

    // Copy assignment operator
    BlackBoxState& operator= (BlackBoxState& other);

    // Copy assignment operator
    BlackBoxState& operator= (const BlackBoxState& other);

  protected:
    void copy(BlackBoxState& other);
    void copy(const BlackBoxState& other);

  public:
    float reward()
    {
      return m_reward;
    }

    float x()
    {
      return m_x;
    }

    float y()
    {
      return m_y;
    }


    float max()
    {
      return m_max;
    }

    float min()
    {
      return m_min;
    }

    std::vector<float>& state()
    {
      return m_state;
    }

    std::vector<unsigned int>& transition()
    {
      return m_transition;
    }

  public:

    void set_transition(std::vector<unsigned int> &transition)
    {
      m_transition = transition;
    }

    void set_transition(const std::vector<unsigned int> &transition)
    {
      m_transition = transition;
    }

  public:
    void save_image_state(std::string file_name);
    void normalise(float min, float max);
    void create_reward();

  private:
    unsigned int m_state_size;
    float m_reward;
    float m_x, m_y;
    float m_max, m_min;

    std::vector<float>        m_state;
    std::vector<unsigned int> m_transition;

  private:
      float rnd();


};


#endif
