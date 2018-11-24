#ifndef _ARCADE_H_
#define _ARCADE_H_



#include "env.h"

#include "arcade_screen.h"
#include "arcade_obstacle.h"

enum AracadePlayerState
{
  PLAYER_STATE_INIT,
  PLAYER_STATE_JUMPING,
  PLAYER_STATE_FALLING
};



class EnvArcade: public Env
{
  protected:
    unsigned int width, height;

    ArcadeScreen screen;

  protected:
    GLVisualisation visualisation;

  protected:

    unsigned int player_y;
    AracadePlayerState player_state;


    std::vector<ArcadeObstacle> obstacles;

  public:
    EnvArcade(unsigned int width = 50, unsigned int height = 32);

    // Copy constructor
    EnvArcade(EnvArcade& other);

    // Copy constructor
    EnvArcade(const EnvArcade& other);

    // Destructor
    virtual ~EnvArcade();

    // Copy assignment operator
    EnvArcade& operator= (EnvArcade& other);

    // Copy assignment operator
    EnvArcade& operator= (const EnvArcade& other);

  protected:
    void copy_arcade(EnvArcade& other);
    void copy_arcade(const EnvArcade& other);

  public:
    void action(unsigned int action_id);
    void print();
    void render();

    void update_state();

};

#endif
