#include "agent_sarsa_table.h"

AgentSarsaTable::AgentSarsaTable()
{
  action      = 0;
  action_prev = 0;
}

AgentSarsaTable::AgentSarsaTable(Env &env, sAgentHyperparameters hyperparameters)
            :Agent(env, hyperparameters)
{
  init(env, hyperparameters);
}


AgentSarsaTable::AgentSarsaTable(const Env &env, sAgentHyperparameters hyperparameters)
            :Agent(env, hyperparameters)
{
  init(env, hyperparameters);
}

AgentSarsaTable::AgentSarsaTable(AgentSarsaTable& other)
            :Agent(other)
{
  copy_agent_q_table(other);
}

AgentSarsaTable::AgentSarsaTable(const AgentSarsaTable& other)
            :Agent(other)
{
  copy_agent_q_table(other);
}

AgentSarsaTable::~AgentSarsaTable()
{

}

AgentSarsaTable& AgentSarsaTable::operator= (AgentSarsaTable& other)
{
  copy(other);
  copy_agent_q_table(other);

  return *this;
}

AgentSarsaTable& AgentSarsaTable::operator= (const AgentSarsaTable& other)
{
  copy(other);
  copy_agent_q_table(other);

  return *this;
}

void AgentSarsaTable::init(Env &env, sAgentHyperparameters hyperparameters)
{
  Agent::init(env, hyperparameters);

  state      = env.get_observation();
  state_prev = state;

  action      = 0;
  action_prev = 0;

  q_table.resize(state.size());
  for (unsigned int j = 0; j < q_table.size(); j++)
  {
    q_table[j].resize(env.get_actions_count());
    for (unsigned int i = 0; i < q_table[j].size(); i++)
      q_table[j][i] = 0.0;
  }
}

void AgentSarsaTable::init(const Env &env, sAgentHyperparameters hyperparameters)
{
  Agent::init(env, hyperparameters);

  state      = this->env->get_observation();
  state_prev = state;

  action      = 0;
  action_prev = 0;


  q_table.resize(state.size());
  for (unsigned int j = 0; j < q_table.size(); j++)
  {
    q_table[j].resize(this->env->get_actions_count());
    for (unsigned int i = 0; i < q_table[j].size(); i++)
      q_table[j][i] = 0.0;
  }
}

void AgentSarsaTable::copy_agent_q_table(AgentSarsaTable &other)
{
  q_table     = other.q_table;
  state       = other.state;
  state_prev  = other.state_prev;

  action      = other.action;
  action_prev = other.action_prev;
}

void AgentSarsaTable::copy_agent_q_table(const AgentSarsaTable &other)
{
  q_table     = other.q_table;
  state       = other.state;
  state_prev  = other.state_prev;

  action      = other.action;
  action_prev = other.action_prev;
}

void AgentSarsaTable::main()
{
  float gamma = hyperparameters.gamma;

  if (state.is_terminal())
    gamma = 0.0;


  state_prev  = state;
  state       = env->get_observation();

  action_prev = action;
  action      = select_action(q_table[state.argmax()]);


  q_table[state_prev.argmax()][action_prev]+=

  hyperparameters.alpha*(env->reward() + gamma*q_table[state.argmax()][action] - q_table[state_prev.argmax()][action_prev]);


  env->action(action);
}
