#include "sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(Json::Value json)
{
  set(json);
}



Sprite::Sprite(Sprite& other)
{
  copy(other);
}

Sprite::Sprite(const Sprite& other)
{
  copy(other);
}

Sprite::~Sprite()
{

}

Sprite& Sprite::operator= (Sprite& other)
{
  copy(other);

  return *this;
}

Sprite& Sprite::operator= (const Sprite& other)
{
  copy(other);

  return *this;
}

void Sprite::copy(Sprite& other)
{
  sprite = other.sprite;
}

void Sprite::copy(const Sprite& other)
{
  sprite = other.sprite;
}

void Sprite::set(Json::Value json)
{
  sprite.name         = json["name"].asString();
  sprite.id           = json["id"].asInt();
  sprite.scale        = json["scale"].asFloat();
  sprite.solid        = json["solid"].asBool();
  sprite.r            = json["color"][0].asFloat();
  sprite.g            = json["color"][1].asFloat();
  sprite.b            = json["color"][2].asFloat();
}

sSprite& Sprite::get()
{
  return sprite;
}

void Sprite::render(GLVisualisation &visualisation, float size)
{
  visualisation.push();


  if (sprite.id != 0) 
  {
    visualisation.set_color(1.0, 1.0, 1.0);
    visualisation.paint_textured_rectangle(size*sprite.scale, size*sprite.scale, sprite.id);
  }
  else
  {
    visualisation.set_color(sprite.r, sprite.g, sprite.b);
    visualisation.paint_square(size*sprite.scale);
  }


  visualisation.pop();
}
