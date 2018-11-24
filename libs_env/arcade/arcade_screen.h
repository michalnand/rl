#ifndef _ARCADE_SCREEN_H_
#define _ARCADE_SCREEN_H_

#include <vector>
#include "visualisation/glvisualisation.h"
#include "arcade_field.h"


struct sArcadeFieldColor
{
  float r, g, b;
};

class ArcadeScreen
{
  private:
    std::vector<std::vector<AracadeField>> screen;

  public:
    ArcadeScreen();
    ArcadeScreen(ArcadeScreen& other);
    ArcadeScreen(const ArcadeScreen& other);

    virtual ~ArcadeScreen();
    ArcadeScreen& operator= (ArcadeScreen& other);
    ArcadeScreen& operator= (const ArcadeScreen& other);

  protected:
    void copy(ArcadeScreen& other);
    void copy(const ArcadeScreen& other);

  public:
    void init(unsigned int width, unsigned int height);

    unsigned int width();
    unsigned int height();

    void set(unsigned int x, unsigned int y, AracadeField value);

    AracadeField get(unsigned int x, unsigned int y);
    sArcadeFieldColor get_color(unsigned int x, unsigned int y);

    void render(GLVisualisation &visualisation);
    void print();

    void clear();
};


#endif
