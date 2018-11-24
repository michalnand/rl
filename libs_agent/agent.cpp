#include "agent.h"


Agent::Agent()
{
  env                     = nullptr;
  actions_count           = 0;

  hyperparameters.alpha   = 0.0;
  hyperparameters.gamma   = 0.0;
  hyperparameters.epsilon = 0.0;
  hyperparameters.epsilon_best = 0.0;

  run_best      = false;
}

Agent::Agent(Agent& other)
{
  copy(other);
}

Agent::Agent(const Agent& other)
{
  copy(other);
}

Agent::Agent(Env &env, sAgentHyperparameters hyperparameters)
{
  init(env, hyperparameters);
}

Agent::Agent(const Env &env, sAgentHyperparameters hyperparameters)
{
  init(env, hyperparameters);
}

Agent::~Agent()
{

}

Agent& Agent::operator= (Agent& other)
{
  copy(other);
  return *this;
}

Agent& Agent::operator= (const Agent& other)
{
  copy(other);
  return *this;
}


void Agent::init(Env &env, sAgentHyperparameters hyperparameters)
{
  this->env             = &env;
  this->hyperparameters = hyperparameters;
  this->actions_count   = this->env->get_actions_count();
  this->run_best      = false;
}

void Agent::init(const Env &env, sAgentHyperparameters hyperparameters)
{
  this->env             = (Env*)&env;
  this->hyperparameters = hyperparameters;
  this->actions_count   = this->env->get_actions_count();
  this->run_best      = false;
}

void Agent::copy(Agent &other)
{
  env               = other.env;
  actions_count     = other.actions_count;
  hyperparameters   = other.hyperparameters;
  run_best          = other.run_best;
}

void Agent::copy(const Agent &other)
{
  env               = other.env;
  actions_count     = other.actions_count;
  hyperparameters   = other.hyperparameters;
  run_best          = other.run_best;
}

void Agent::main()
{
  unsigned int action_id = rand()%actions_count;
  env->action(action_id);
}



unsigned int Agent::select_action(std::vector<float> &q_values)
{
  unsigned int result = 0;

  for (unsigned int i = 0; i < q_values.size(); i++)
    if (q_values[i] > q_values[result])
      result = i;

  float epsilon;
  if (run_best == true)
    epsilon = hyperparameters.epsilon_best;
  else
    epsilon = hyperparameters.epsilon;

  float v = (rand()%100000)/100000.0;
  if (v < epsilon)
    result = rand()%q_values.size();

  return result;
}
 
float Agent::max(std::vector<float> &v)
{
  unsigned int max_i = 0;

  for (unsigned int i = 0; i < v.size(); i++)
    if (v[i] > v[max_i])
      max_i = i;

  return v[max_i];
}
