#include "rl_log.h"

RLLog::RLLog()
{
  iterations_to_log = 1000;
}

RLLog::~RLLog()
{

}

void RLLog::set_file_name_prefix(std::string file_name_prefix)
{
  std::string progress_log_file_name = file_name_prefix + "rl_progress.log";

  progress_log.set_output_file_name(progress_log_file_name);
}

void RLLog::add(Env &env, Agent &agent, bool log_all)
{
  (void)agent;
  if (((env.iteration()%iterations_to_log) == 0) || log_all)
  {
    float normalised_score = env.score()*1.0/(env.iteration()+1);

    progress_log << env.iteration() << " " << env.score() << " " << env.reward() << " " << normalised_score << "\n";

    sRLScoreLogItem item;
    item.iteration         = env.iteration();
    item.score             = env.score();
    item.normalised_score  = normalised_score;
    item.reward            = env.reward();

    score.push_back(item);
  }
}

std::vector<sRLScoreLogItem>& RLLog::get_score_log()
{
  return score;
}
