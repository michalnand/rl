#ifndef _RL_SUMMARY_RESULT_H_
#define _RL_SUMMARY_RESULT_H_

#include <rl_log.h>
#include <histogram.h>

class RLSummaryResult
{
  private:

    std::vector<std::vector<sRLScoreLogItem>> experiment_logs;

    std::vector<float> score_average;
    std::vector<float> score_min;
    std::vector<float> score_max;

    Histogram score_histogram;

  public:

    RLSummaryResult();
    virtual ~RLSummaryResult();

    void add(std::vector<sRLScoreLogItem>& experiment_log);
    void compute();
    void save(std::string file_name_prefix);

  private:
    unsigned int compute_items_count();


};

#endif
