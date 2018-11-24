#ifndef _AGENT_DQN_H_
#define _AGENT_DQN_H_


#include "agent.h"
#include <string>
#include <dqn.h>


class AgentDQN: public Agent
{
  private:
    std::string json_config_file_name;
    JsonConfig json_config;

    DQN dqn;

  public:
    AgentDQN();

    AgentDQN(Env &env, std::string json_config_file_name);
    AgentDQN(const Env &env, std::string json_config_file_name);

    AgentDQN(AgentDQN& other);

    AgentDQN(const AgentDQN& other);

    virtual ~AgentDQN();
    AgentDQN& operator= (AgentDQN& other);
    AgentDQN& operator= (const AgentDQN& other);

    void init(Env &env, std::string json_config_file_name);
    void init(const Env &env, std::string json_config_file_name);

  protected:
    void init_(std::string json_config_file_name);

  protected:
    void copy_agent_dqn(AgentDQN &other);
    void copy_agent_dqn(const AgentDQN &other);

  public:
    void main();
};


#endif
