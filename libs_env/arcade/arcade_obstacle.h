#ifndef _ARCADE_OBSTACLE_H_
#define _ARCADE_OBSTACLE_H_

#include "arcade_field.h"
#include "arcade_screen.h"

class ArcadeObstacle
{
  protected:
    int x, y;
    AracadeField field_type;
    std::vector<std::vector<AracadeField>> obstacle;

  public:
    ArcadeObstacle();
    virtual ~ArcadeObstacle();

    void create(unsigned int x, unsigned int y, unsigned int max_width, unsigned int max_height, AracadeField field);

    void add_to_screen(ArcadeScreen &screen);
    bool is_out(ArcadeScreen &screen);
    bool is_colission(unsigned int pos_x, unsigned int pos_y);
    void move(int dx, int dy);

    AracadeField get_type();
};

#endif
