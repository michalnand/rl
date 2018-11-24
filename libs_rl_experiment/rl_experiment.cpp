#include "rl_experiment.h"

RLExperiment::RLExperiment(std::string config_file_name)
{
  json_config.load(config_file_name);
}

RLExperiment::~RLExperiment()
{

}

void RLExperiment::run(Env &env, Agent &agent)
{
  std::string log_file_name_prefix = json_config.result["log_file_name_prefix"].asString();

  summary_log.set_output_file_name(log_file_name_prefix + "summary.log");

  training_rl_log.set_file_name_prefix(log_file_name_prefix + "training_");

  testing_rl_log.set_file_name_prefix(log_file_name_prefix + "testing_");


  unsigned int training_iterations  = json_config.result["training_iterations"].asInt();
  unsigned int testing_iterations   = json_config.result["testing_iterations"].asInt();
  unsigned int visual_iterations    = json_config.result["visual_iterations"].asInt();
  env.reset_score();


  summary_log << "starting\n\n";
  summary_log << "result log path " << log_file_name_prefix << "\n";
  summary_log << "training iterations " << training_iterations << "\n";
  summary_log << "testing iterations " << testing_iterations << "\n";
  summary_log << "\n";

  summary_log << "training\n";


  for (unsigned int i = 0; i < training_iterations; i++)
  {
    agent.main();
    training_rl_log.add(env, agent);
  }

  summary_log << "training score " << env.score() << "\n";
  summary_log << "normalised training score " << env.score()/training_iterations << "\n";

  summary_log << "\n";

  summary_log << "testing\n";


  env.reset_score();
  agent.run_best_enable();

  for (unsigned int i = 0; i < testing_iterations; i++)
  {
    agent.main();
    testing_rl_log.add(env, agent, true);
  }


  summary_log << "testing score " << env.score() << "\n";
  summary_log << "normalised testing score " << env.score()/testing_iterations << "\n";

  summary_log << "\n";



  if (json_config.result["run_visual"].asBool())
  {
    env.reset_score();
    agent.run_best_enable();

    for (unsigned int i = 0; i < visual_iterations; i++)
    {
      env.print();
      env.render();
      agent.main();
      env.delay_ms(5);
    }
  }

  summary_log << "done\n\n";
}


std::vector<sRLScoreLogItem>& RLExperiment::get_training_score_log()
{
  return training_rl_log.get_score_log();
}

std::vector<sRLScoreLogItem>& RLExperiment::get_testing_score_log()
{
  return testing_rl_log.get_score_log();
}
