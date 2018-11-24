#ifndef _RL_LOG_H_
#define _RL_LOG_H_

#include <vector>
#include <string>

#include <agent.h>
#include <env.h>

#include <log.h>

struct sRLScoreLogItem
{
  unsigned int iteration;
  float score;
  float normalised_score;
  float reward;
};

class RLLog
{
  private:
    unsigned int iterations_to_log;

    Log progress_log;

    std::vector<sRLScoreLogItem>score;

  public:
    RLLog();
    virtual ~RLLog();

    void set_file_name_prefix(std::string file_name_prefix);
    void add(Env &env, Agent &agent, bool log_all = false);

    std::vector<sRLScoreLogItem>& get_score_log();

};


#endif
