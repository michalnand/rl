#ifndef _RL_EXPERIMENT_H_
#define _RL_EXPERIMENT_H_

#include <json_config.h>
#include <rl_log.h>
#include <agent.h>
#include <env.h>

class RLExperiment
{
  protected:
    JsonConfig json_config;

    Log summary_log;
    RLLog training_rl_log;
    RLLog testing_rl_log;

  public:
    RLExperiment(std::string config_file_name);
    virtual ~RLExperiment();

    void run(Env &env, Agent &agent);

    std::vector<sRLScoreLogItem>& get_training_score_log();
    std::vector<sRLScoreLogItem>& get_testing_score_log();

};


#endif
