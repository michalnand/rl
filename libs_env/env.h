#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <state.h>

class Env
{
  protected:
    State m_state;

    unsigned int m_actions_count;
    float m_reward;
    float m_score;

    bool m_done;

    unsigned int m_epoch, m_iteration;

   public:
    Env();
    Env(std::string path);

    Env(Env& other);

    Env(const Env& other);

    virtual ~Env();
    virtual Env& operator= (Env& other);
    virtual Env& operator= (const Env& other);

  protected:
    void copy(Env &other);
    void copy(const Env &other);

  public:
    State& get_observation()
    {
      return m_state;
    }

    unsigned int get_actions_count()
    {
      return m_actions_count;
    }

    bool is_done()
    {
      return m_done;
    }

    float reward()
    {
      return m_reward;
    }

    float score()
    {
      return m_score;
    }

    void reset_score()
    {
      m_score = 0.0;
      m_iteration = 0;
    }

    unsigned int iteration()
    {
      return m_iteration;
    }

    unsigned int epoch()
    {
      return m_epoch;
    }

    void delay_ms(unsigned long int ms_time);

  public:
    virtual void action(unsigned int action_id);

  public:
    virtual void save(std::string path);
    virtual void load(std::string path);

  public:
    virtual void print();
    virtual void render();
    virtual void monitor();
    virtual int get_key()
    {
      return -1;
    }

  protected:
    void process_step();

    public:
	       State& get_state()
           {
               return m_state;
           }


           void set_actions_count(unsigned int actions_count)
           {
               m_actions_count = actions_count;
           }

           float get_reward()
           {
               return m_reward;
           }

           void set_reward(float reward)
           {
               m_reward = reward;
           }

           float get_score()
           {
               return m_score;
           }

           void set_score(float score)
           {
               m_score = score;
           }

           bool get_done()
           {
               return m_done;
           }

           void set_done(bool done)
           {
               m_done = done;
           }
};

#endif
