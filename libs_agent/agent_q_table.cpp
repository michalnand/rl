#include "agent_q_table.h"

AgentQTable::AgentQTable()
{
  action      = 0;
  action_prev = 0;
}

AgentQTable::AgentQTable(Env &env, sAgentHyperparameters hyperparameters)
            :Agent(env, hyperparameters)
{
  init(env, hyperparameters);
}


AgentQTable::AgentQTable(const Env &env, sAgentHyperparameters hyperparameters)
            :Agent(env, hyperparameters)
{
  init(env, hyperparameters);
}

AgentQTable::AgentQTable(AgentQTable& other)
            :Agent(other)
{
  copy_agent_q_table(other);
}

AgentQTable::AgentQTable(const AgentQTable& other)
            :Agent(other)
{
  copy_agent_q_table(other);
}

AgentQTable::~AgentQTable()
{

}

AgentQTable& AgentQTable::operator= (AgentQTable& other)
{
  copy(other);
  copy_agent_q_table(other);

  return *this;
}

AgentQTable& AgentQTable::operator= (const AgentQTable& other)
{
  copy(other);
  copy_agent_q_table(other);

  return *this;
}

void AgentQTable::init(Env &env, sAgentHyperparameters hyperparameters)
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

void AgentQTable::init(const Env &env, sAgentHyperparameters hyperparameters)
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

void AgentQTable::copy_agent_q_table(AgentQTable &other)
{
  q_table     = other.q_table;
  state       = other.state;
  state_prev  = other.state_prev;

  action      = other.action;
  action_prev = other.action_prev;
}

void AgentQTable::copy_agent_q_table(const AgentQTable &other)
{
  q_table     = other.q_table;
  state       = other.state;
  state_prev  = other.state_prev;

  action      = other.action;
  action_prev = other.action_prev;
}

void AgentQTable::main()
{
  state_prev  = state;
  state       = env->get_observation();

  action_prev = action;
  action      = select_action(q_table[state.argmax()]);

  float gamma = hyperparameters.gamma;

  if (state.is_terminal())
    gamma = 0.0;


  q_table[state_prev.argmax()][action_prev]+=

  hyperparameters.alpha*(env->reward() + gamma*max(q_table[state.argmax()]) - q_table[state_prev.argmax()][action_prev]);


  env->action(action);
}
