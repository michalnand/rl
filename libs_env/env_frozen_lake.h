#ifndef _FROZEN_LAKE_H_
#define _FROZEN_LAKE_H_

#include "env.h"

class EnvFrozenLake: public Env
{
  protected:
    unsigned int m_size;
    int x_pos, y_pos;
    std::vector<std::vector<float>> rewards;

  public:
    // Default constructor
    EnvFrozenLake();

    // Copy constructor
    EnvFrozenLake(EnvFrozenLake& other);

    // Copy constructor
    EnvFrozenLake(const EnvFrozenLake& other);

    // Destructor
    virtual ~EnvFrozenLake();

    // Copy assignment operator
    EnvFrozenLake& operator= (EnvFrozenLake& other);

    // Copy assignment operator
    EnvFrozenLake& operator= (const EnvFrozenLake& other);

  protected:
    void copy_frozen_lake(EnvFrozenLake& other);
    void copy_frozen_lake(const EnvFrozenLake& other);

  public:
    void action(unsigned int action_id);
    void print();

  private:
    int min(int a, int b);
    int max(int a, int b);
    void update_state();


};


#endif
