#include "agent_dqn.h"
#include <iostream>

AgentDQN::AgentDQN()
{

}

AgentDQN::AgentDQN(Env &env, std::string json_config_file_name)
         :Agent(env)
{
  init(env, json_config_file_name);
}


AgentDQN::AgentDQN(const Env &env, std::string json_config_file_name)
         :Agent(env)
{
  init(env, json_config_file_name);
}

AgentDQN::AgentDQN(AgentDQN& other)
            :Agent(other)
{
  copy_agent_dqn(other);
}

AgentDQN::AgentDQN(const AgentDQN& other)
            :Agent(other)
{
  copy_agent_dqn(other);
}

AgentDQN::~AgentDQN()
{

}

AgentDQN& AgentDQN::operator= (AgentDQN& other)
{
  copy(other);
  copy_agent_dqn(other);

  return *this;
}

AgentDQN& AgentDQN::operator= (const AgentDQN& other)
{
  copy(other);
  copy_agent_dqn(other);

  return *this;
}

void AgentDQN::init(Env &env, std::string json_config_file_name)
{
  Agent::init(env, hyperparameters);

  init_(json_config_file_name);
}


void AgentDQN::init(const Env &env, std::string json_config_file_name)
{
  Agent::init(env, hyperparameters);

  init_(json_config_file_name);
}

void AgentDQN::init_(std::string json_config_file_name)
{
  this->json_config_file_name = json_config_file_name;
  json_config.load(json_config_file_name);


  float gamma                         = json_config.result["gamma"].asFloat();
  unsigned int actions_count          = env->get_actions_count();
  unsigned int experience_buffer_size = json_config.result["experience_buffer_size"].asInt();

  hyperparameters.gamma = gamma;
  hyperparameters.alpha = 1.0;
  hyperparameters.epsilon = json_config.result["epsilon"].asFloat();
  hyperparameters.epsilon_best = json_config.result["epsilon_best"].asFloat();

  auto state = env->get_observation();

  sGeometry state_geometry;
  state_geometry.w = state.w();
  state_geometry.h = state.h();
  state_geometry.d = state.d();

  dqn.init(json_config.result["network_architecture"], gamma, state_geometry, actions_count, experience_buffer_size);
}

void AgentDQN::copy_agent_dqn(AgentDQN &other)
{
  init(*other.env, other.json_config_file_name);
}

void AgentDQN::copy_agent_dqn(const AgentDQN &other)
{
  init(*other.env, other.json_config_file_name);
}

void AgentDQN::main()
{
  auto  state            = env->get_observation();
  auto  state_vector     = state.get();

  dqn.compute_q_values(state_vector);

  auto q_values = dqn.get_q_values();

  unsigned int action      = select_action(q_values);


  env->action(action);

  float        reward      = env->reward();

  if (env->is_done())
    dqn.add_final(state_vector, q_values, action, reward);
  else
    dqn.add(state_vector, q_values, action, reward);

  if (dqn.is_full())
  {
    dqn.learn();
  }
}
