#include "rl_summary_result.h"
#include <iostream>

RLSummaryResult::RLSummaryResult()
{

}

RLSummaryResult::~RLSummaryResult()
{

}

void RLSummaryResult::add(std::vector<sRLScoreLogItem>& experiment_log)
{
  experiment_logs.push_back(experiment_log);
}

void RLSummaryResult::compute()
{
  unsigned int items_count        = compute_items_count();
  unsigned int experiments_count  = experiment_logs.size();

  std::cout << "items_count" << items_count << "\n";
  std::cout << "experiments_count" << experiments_count << "\n";

  score_average.resize(items_count);
  score_min.resize(items_count);
  score_max.resize(items_count);

  for (unsigned int j = 0; j < items_count; j++)
  {
    float average = 0.0;
    for (unsigned int i = 0; i < experiments_count; i++)
      average+= experiment_logs[i][j].score;
    average = average/experiments_count;


    float min = experiment_logs[0][j].score;
    for (unsigned int i = 0; i < experiments_count; i++)
      if (min > experiment_logs[i][j].score)
        min = experiment_logs[i][j].score;


    float max = experiment_logs[0][j].score;
    for (unsigned int i = 0; i < experiments_count; i++)
      if (max < experiment_logs[i][j].score)
        max = experiment_logs[i][j].score;

    for (unsigned int i = 0; i < experiments_count; i++)
      score_histogram.add(experiment_logs[i][j].score);

    score_average[j]  = average;
    score_min[j]      = min;
    score_max[j]      = max;
  }


  score_histogram.compute(101);
}

void RLSummaryResult::save(std::string file_name_prefix)
{
  score_histogram.save(file_name_prefix+"histogram.log");

  Log log(file_name_prefix + "score.log");

  for (unsigned int i = 0; i < score_average.size(); i++)
  {
    log << i << " ";
    log << score_average[i] << " ";
    log << score_min[i] << " ";
    log << score_max[i] << " ";
    log << "\n";
  }
}

unsigned int RLSummaryResult::compute_items_count()
{
  unsigned int result = experiment_logs[0].size();

  for (unsigned int j = 0; j < experiment_logs.size(); j++)
    if (experiment_logs[j].size() < result)
      result = experiment_logs[j].size();

  return result;
}
