#include "arcade_screen.h"

#include <iostream>

ArcadeScreen::ArcadeScreen()
{

}

ArcadeScreen::ArcadeScreen(ArcadeScreen& other)
{
  copy(other);
}

ArcadeScreen::ArcadeScreen(const ArcadeScreen& other)
{
  copy(other);
}

ArcadeScreen::~ArcadeScreen()
{

}

ArcadeScreen& ArcadeScreen::operator= (ArcadeScreen& other)
{
  copy(other);

  return *this;
}

ArcadeScreen& ArcadeScreen::operator= (const ArcadeScreen& other)
{
  copy(other);

  return *this;
}

void ArcadeScreen::copy(ArcadeScreen& other)
{
  screen = other.screen;
}

void ArcadeScreen::copy(const ArcadeScreen& other)
{
  screen = other.screen;
}





void ArcadeScreen::init(unsigned int width, unsigned int height)
{
  screen.resize(height);
  for (unsigned int j = 0; j < height; j++)
    screen[j].resize(width);

  for (unsigned int j = 0; j < height; j++)
  for (unsigned int i = 0; i < width; i++)
    screen[j][i] = AF_EMPTY;
}

unsigned int ArcadeScreen::width()
{
  return screen[0].size();
}

unsigned int ArcadeScreen::height()
{
  return screen.size();
}

void ArcadeScreen::set(unsigned int x, unsigned int y, AracadeField value)
{
  screen[y][x] = value;
}

AracadeField ArcadeScreen::get(unsigned int x, unsigned int y)
{
  return screen[y][x];
}

sArcadeFieldColor ArcadeScreen::get_color(unsigned int x, unsigned int y)
{
  AracadeField field = get(x, y);

  sArcadeFieldColor result;

  switch (field)
  {
    case AF_EMPTY   : result.r = 0.0; result.g = 0.0; result.b = 0.0; break;
    case AF_COMMON  : result.r = 0.5; result.g = 0.5; result.b = 0.5; break;
    case AF_OBSTACLE: result.r = 1.0; result.g = 0.0; result.b = 0.0; break;
    case AF_POINT   : result.r = 0.0; result.g = 1.0; result.b = 0.0; break;
    case AF_PLAYER  : result.r = 0.0; result.g = 0.0; result.b = 1.0; break;

    default: result.r = 1.0; result.g = 1.0; result.b = 1.0; break;
  }

  return result;
}

void ArcadeScreen::render(GLVisualisation &visualisation)
{
  float element_width   = 0.4*4.0/width();
  float element_height  = 0.4*4.0/width();

  /*
  float window_width  = visualisation.width();
  float window_height = visualisation.height();
  */
  //float ratio = window_width/window_height;

  visualisation.push();

  for (unsigned int y = 0; y < height(); y++)
  {
    for (unsigned int x = 0; x < width(); x++)
    {
      sArcadeFieldColor color = get_color(x, y);

      float x_ = 2.0*(x*1.0/width() - 0.5);
      float y_ = 2.0*(y*1.0/width() - 0.5);

      visualisation.push();

        visualisation.translate(x_, y_, 0.0);
        visualisation.set_color(color.r + 0.1, color.g + 0.1, color.b + 0.1);
        visualisation.paint_rectangle(element_width, element_height);

      visualisation.pop();
    }
  }

  visualisation.pop();
}

void ArcadeScreen::print()
{
  for (unsigned int y = 0; y < height(); y++)
  {
    for (unsigned int x = 0; x < width(); x++)
      std::cout << get(x, y) << " ";
    std::cout << "\n";
  }

  std::cout << "\n";
}

void ArcadeScreen::clear()
{
  for (unsigned int y = 0; y < height(); y++)
  {
    for (unsigned int x = 0; x < width(); x++)
      screen[y][x] = AF_EMPTY;
  }
}
