#ifndef _BALL_BALANCE_H_
#define _BALL_BALANCE_H_



#include "env.h"

#include "visualisation/glvisualisation.h"

class EnvBallBalance: public Env
{
  private:
    float target_radius;
    float dt;
    float board_inertia;
    float ball_mass;
    float friction;

    float angle_x, angle_y;
    float vx, vy;
    float x, y;

    float x_1, y_1;
    float x_2, y_2;
    float x_3, y_3;

  private:
    int size;

  protected:
    GLVisualisation visualisation;


  public:
    EnvBallBalance(unsigned int size = 16);

    // Copy constructor
    EnvBallBalance(EnvBallBalance& other);

    // Copy constructor
    EnvBallBalance(const EnvBallBalance& other);

    // Destructor
    virtual ~EnvBallBalance();

    // Copy assignment operator
    EnvBallBalance& operator= (EnvBallBalance& other);

    // Copy assignment operator
    EnvBallBalance& operator= (const EnvBallBalance& other);

  protected:
    void copy_ball_balance(EnvBallBalance& other);
    void copy_ball_balance(const EnvBallBalance& other);

  public:
    void action(unsigned int action_id);
    void print();
    void render();

    int get_key();

  private:
    void reset();
    void process_move(float r_angle_x, float r_angle_y);
    void update_state();


    float vpos(float pos);
    float rnd(float min, float max);


};

#endif
