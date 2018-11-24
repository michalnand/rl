#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <json_config.h>
#include "visualisation/glvisualisation.h"

struct sSprite
{
  std::string name;
  unsigned int id;
  float scale;
  bool solid;
  float r, g, b;
};


class Sprite
{
  private:
    sSprite sprite;

  public:
    Sprite();
    Sprite(Json::Value json);
    Sprite(Sprite& other);
    Sprite(const Sprite& other);

    virtual ~Sprite();

    Sprite& operator= (Sprite& other);
    Sprite& operator= (const Sprite& other);

  protected:
    void copy(Sprite& other);
    void copy(const Sprite& other);


  public:
    void set(Json::Value json);
    sSprite& get();
    void render(GLVisualisation &visualisation, float size = 1.0);
};

#endif
