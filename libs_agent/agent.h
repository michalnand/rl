#ifndef _AGENT_H_
#define _AGENT_H_

#include <state.h>
#include <env.h>
#include "agent_hyperparameters.h"

class Agent
{
  protected:
    Env *env;
    unsigned int actions_count;

    sAgentHyperparameters hyperparameters;

    bool run_best;

  public:
    Agent();

    Agent(Env &env, sAgentHyperparameters hyperparameters = {0, 0, 0, 0});
    Agent(const Env &env, sAgentHyperparameters hyperparameters = {0, 0, 0, 0});

    Agent(Agent& other);

    Agent(const Agent& other);

    virtual ~Agent();
    virtual Agent& operator= (Agent& other);
    virtual Agent& operator= (const Agent& other);


    virtual void init(Env &env, sAgentHyperparameters hyperparameters);
    virtual void init(const Env &env, sAgentHyperparameters hyperparameters);

  protected:
    void copy(Agent &other);
    void copy(const Agent &other);

  public:
    virtual void main();

    virtual unsigned int select_action(std::vector<float> &q_values);
    virtual float max(std::vector<float> &v);


    void run_best_enable()
    {
      run_best = true;
    }

    void run_best_disable()
    {
      run_best = false;
    }

    bool run_best_enabled()
    {
      return run_best;
    }

    void set_epsilon(float epsilon)
    {
      hyperparameters.epsilon = epsilon;
    }

};


#endif
