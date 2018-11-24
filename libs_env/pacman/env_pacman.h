#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <vector>
#include <map>

#include "env.h"

#include "visualisation/glvisualisation.h"

#include "position.h"
#include "sprite.h"

struct sEnvPacManPosition
{
  int x, y;
};

class EnvPacman: public Env
{
  protected:
    JsonConfig json;

    unsigned int width, height;

    std::vector<Sprite> sprites;
    std::map<unsigned int, unsigned int> sprites_mapped;
    std::vector<std::vector<unsigned int>> grid;

    std::vector<sPosition> player_position, enemy_position;

    std::vector<int> enemy_state;

  protected:
    GLVisualisation visualisation;


  public:
    EnvPacman(std::string config_file_name);

    // Copy constructor
    EnvPacman(EnvPacman& other);

    // Copy constructor
    EnvPacman(const EnvPacman& other);

    // Destructor
    virtual ~EnvPacman();

    // Copy assignment operator
    EnvPacman& operator= (EnvPacman& other);

    // Copy assignment operator
    EnvPacman& operator= (const EnvPacman& other);

  protected:
    void copy_pacman(EnvPacman& other);
    void copy_pacman(const EnvPacman& other);

  public:
    void action(unsigned int action_id);
    void print();
    void render();

  private:
    void init_game(Json::Value &json);
    void game_reset();

    void reset();
    void player_reset();
    void update_state();

    float vposx(int x);
    float vposy(int y);

    bool move_right(sPosition &position);
    bool move_left(sPosition &position);
    bool move_up(sPosition &position);
    bool move_down(sPosition &position);

    void process_enemy_move(sPosition &position, int &state);
    int is_cross_road(sPosition &position);


};

#endif
