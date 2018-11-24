#ifndef _AGENT_Q_TABLE_H_
#define _AGENT_Q_TABLE_H_


#include "agent.h"
#include <vector>

class AgentQTable: public Agent
{
  private:
    State state, state_prev;
    unsigned int action, action_prev;

    std::vector<std::vector<float>> q_table;

  public:
    AgentQTable();

    AgentQTable(Env &env, sAgentHyperparameters hyperparameters);
    AgentQTable(const Env &env, sAgentHyperparameters hyperparameters);

    AgentQTable(AgentQTable& other);

    AgentQTable(const AgentQTable& other);

    virtual ~AgentQTable();
    AgentQTable& operator= (AgentQTable& other);
    AgentQTable& operator= (const AgentQTable& other);

    void init(Env &env, sAgentHyperparameters hyperparameters);
    void init(const Env &env, sAgentHyperparameters hyperparameters);

  protected:
    void copy_agent_q_table(AgentQTable &other);
    void copy_agent_q_table(const AgentQTable &other);

  public:
    void main();
};


#endif
