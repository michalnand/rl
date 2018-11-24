#ifndef _AGENT_DQNP_H_
#define _AGENT_DQNP_H_


#include "agent.h"
#include <string>
#include <dqnp.h>


class AgentDQNP: public Agent
{
  private:
    std::string json_config_file_name;
    JsonConfig json_config;

    DQNP dqn;

  public:
    AgentDQNP();

    AgentDQNP(Env &env, std::string json_config_file_name);
    AgentDQNP(const Env &env, std::string json_config_file_name);

    AgentDQNP(AgentDQNP& other);

    AgentDQNP(const AgentDQNP& other);

    virtual ~AgentDQNP();
    AgentDQNP& operator= (AgentDQNP& other);
    AgentDQNP& operator= (const AgentDQNP& other);

    void init(Env &env, std::string json_config_file_name);
    void init(const Env &env, std::string json_config_file_name);

  protected:
    void init_(std::string json_config_file_name);

  protected:
    void copy_agent_dqn(AgentDQNP &other);
    void copy_agent_dqn(const AgentDQNP &other);

  public:
    void main();
};


#endif
