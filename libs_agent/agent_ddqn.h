#ifndef _AGENT_DDQN_H_
#define _AGENT_DDQN_H_


#include "agent.h"
#include <string>

#include <ddqn.h>


class AgentDDQN: public Agent
{
  private:
    std::string json_config_file_name;
    JsonConfig json_config;

    DDQN dqn;
 
  public:
    AgentDDQN();

    AgentDDQN(Env &env, std::string json_config_file_name);
    AgentDDQN(const Env &env, std::string json_config_file_name);

    AgentDDQN(AgentDDQN& other);

    AgentDDQN(const AgentDDQN& other);

    virtual ~AgentDDQN();
    AgentDDQN& operator= (AgentDDQN& other);
    AgentDDQN& operator= (const AgentDDQN& other);

    void init(Env &env, std::string json_config_file_name);
    void init(const Env &env, std::string json_config_file_name);

  protected:
    void init_(std::string json_config_file_name);

  protected:
    void copy_agent_dqn(AgentDDQN &other);
    void copy_agent_dqn(const AgentDDQN &other);

  public:
    void main();
};


#endif
