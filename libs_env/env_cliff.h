#ifndef _CLIFF_H_
#define _CLIFF_H_

#include "env.h"

#include "visualisation/glvisualisation.h"


class EnvCliff: public Env
{
  protected:
    unsigned int m_size;
    int x_pos, y_pos;
    std::vector<std::vector<float>> rewards;

    GLVisualisation visualisation;

  public:
    // Default constructor
    EnvCliff(unsigned int size = 8);

    // Copy constructor
    EnvCliff(EnvCliff& other);

    // Copy constructor
    EnvCliff(const EnvCliff& other);

    // Destructor
    virtual ~EnvCliff();

    // Copy assignment operator
    EnvCliff& operator= (EnvCliff& other);

    // Copy assignment operator
    EnvCliff& operator= (const EnvCliff& other);

  protected:
    void copy_cliff(EnvCliff& other);
    void copy_cliff(const EnvCliff& other);

  public:
    void action(unsigned int action_id);
    void print();
    void render();

  private:
    int min(int a, int b);
    int max(int a, int b);
    float vpos(float pos);
    void update_state();


};


#endif
