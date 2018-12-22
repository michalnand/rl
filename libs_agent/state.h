#ifndef _STATE_H_
#define _STATE_H_

#include <vector>
#include <string>

class State
{
  protected:
    unsigned int m_w, m_h, m_d, m_size;
    std::vector<float> m_state;

    bool m_terminal;

  public:
    State();
    State(State& other);
    State(const State& other);

    State(unsigned int w, unsigned int h = 1, unsigned int d = 1);


    virtual ~State();
    State& operator= (State& other);
    State& operator= (const State& other);

    void init(unsigned int w, unsigned h = 1, unsigned d = 1);

  protected:
    void copy(State& other);
    void copy(const State& other);

  public:
    std::vector<float>& get();
    void set(std::vector<float> &state);
    void set_element(float value, unsigned int w, unsigned int h = 0, unsigned int d = 0);
    float get_element(unsigned int w, unsigned int h = 0, unsigned int d = 0);
    void clear();

    bool is_terminal();
    void set_terminal();
    void set_no_terminal();

  public:

    virtual std::string as_string(unsigned int precision = 3);
    void print(unsigned int precision = 3);

    bool is_valid();

  public:
    void random(float range = 1.0);
    void add_noise(float level);

    unsigned int argmax();
    unsigned int argmin();

    float dot(State& other);
    float distance(State& other);

    void normalise();

  public:
    unsigned int w()
    {
      return m_w;
    }

    unsigned int h()
    {
      return m_h;
    }

    unsigned int d()
    {
      return m_d;
    }

    unsigned int size()
    {
      return m_size;
    }

  private:
    float randf();



};

#endif
