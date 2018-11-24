#ifndef _AGENT_SARSA_TABLE_H_
#define _AGENT_SARSA_TABLE_H_


#include "agent.h"
#include <vector>

class AgentSarsaTable: public Agent
{
  private:
    State state, state_prev;
    unsigned int action, action_prev;

    std::vector<std::vector<float>> q_table;

  public:
    AgentSarsaTable();

    AgentSarsaTable(Env &env, sAgentHyperparameters hyperparameters);
    AgentSarsaTable(const Env &env, sAgentHyperparameters hyperparameters);

    AgentSarsaTable(AgentSarsaTable& other);

    AgentSarsaTable(const AgentSarsaTable& other);

    virtual ~AgentSarsaTable();
    AgentSarsaTable& operator= (AgentSarsaTable& other);
    AgentSarsaTable& operator= (const AgentSarsaTable& other);

    void init(Env &env, sAgentHyperparameters hyperparameters);
    void init(const Env &env, sAgentHyperparameters hyperparameters);

  protected:
    void copy_agent_q_table(AgentSarsaTable &other);
    void copy_agent_q_table(const AgentSarsaTable &other);

  public:
    void main();
};


#endif
