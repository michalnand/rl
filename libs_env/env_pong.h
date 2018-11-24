#ifndef _PONG_H_
#define _PONG_H_



#include "env.h"

#include "visualisation/glvisualisation.h"

class EnvPong: public Env
{ 
  protected:
    int size, player_size;

    int ball_x, ball_y;
    int ball_dx, ball_dy;
    int player_a, player_b;

  protected:
    GLVisualisation visualisation;


  public:
    EnvPong(unsigned int size = 32);

    // Copy constructor
    EnvPong(EnvPong& other);

    // Copy constructor
    EnvPong(const EnvPong& other);

    // Destructor
    virtual ~EnvPong();

    // Copy assignment operator
    EnvPong& operator= (EnvPong& other);

    // Copy assignment operator
    EnvPong& operator= (const EnvPong& other);

  protected:
    void copy_pong(EnvPong& other);
    void copy_pong(const EnvPong& other);

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
