#ifndef _CATCHER_H_
#define _CATCHER_H_



#include "env.h"

#include "visualisation/glvisualisation.h"

class EnvCatcher: public Env
{
  protected:
    int size;
    int target_size, target_position_y, target_position_x;
    int agent_position, agent_size;

  protected:
    GLVisualisation visualisation;


  public:
    EnvCatcher(unsigned int size = 32);

    // Copy constructor
    EnvCatcher(EnvCatcher& other);

    // Copy constructor
    EnvCatcher(const EnvCatcher& other);

    // Destructor
    virtual ~EnvCatcher();

    // Copy assignment operator
    EnvCatcher& operator= (EnvCatcher& other);

    // Copy assignment operator
    EnvCatcher& operator= (const EnvCatcher& other);

  protected:
    void copy_catcher(EnvCatcher& other);
    void copy_catcher(const EnvCatcher& other);

  public:
    void action(unsigned int action_id);
    void print();
    void render();

  private:
    void reset();
    void update_state();

    int min(int a, int b);
    int max(int a, int b);
    float vpos(float pos);


};

#endif
