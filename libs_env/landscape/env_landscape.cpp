#include "env_landscape.h"
#include <math.h>

EnvLandscape::EnvLandscape()
            :Env()
{
  width   = 1024;
  height  = 1024;


  surface.resize(height);
  for (unsigned int j = 0; j < height; j++)
  {
    surface[j].resize(width);

    for (unsigned int i = 0; i < width; i++)
      surface[j][i] = 0.0;
  }

  noise.init(4.0, 16, rand());

  generate();
  normalise();

  landscape_render.init(width, height, "landscape_config.json");
}


EnvLandscape::EnvLandscape(EnvLandscape& other)
            :Env(other)
{
  copy_blackbox(other);
}

EnvLandscape::EnvLandscape(const EnvLandscape& other)
            :Env(other)
{
  copy_blackbox(other);
}

EnvLandscape::~EnvLandscape()
{

}

EnvLandscape& EnvLandscape::operator= (EnvLandscape& other)
{
  Env::copy(other);
  copy_blackbox(other);

  return *this;
}

EnvLandscape& EnvLandscape::operator= (const EnvLandscape& other)
{
  Env::copy(other);
  copy_blackbox(other);

  return *this;
}

void EnvLandscape::copy_blackbox(EnvLandscape& other)
{
  width   = other.width;
  height  = other.height;
  surface = other.surface;
}

void EnvLandscape::copy_blackbox(const EnvLandscape& other)
{
  width   = other.width;
  height  = other.height;
  surface = other.surface;
}



void EnvLandscape::render()
{

  landscape_render.render(surface);
}





void EnvLandscape::generate()
{
  for (unsigned int y = 0; y < height; y++)
  for (unsigned int x = 0; x < width; x++)
  {
    float x_ = (x*10.0)/width;
    float y_ = (y*10.0)/height;

    float n = exp(noise.get(x_, y_ ));
    surface[y][x] = n;
  }
}

void EnvLandscape::normalise()
{
  float max = surface[0][0];
  float min = max;

  for (unsigned int y = 0; y < height; y++)
  for (unsigned int x = 0; x < width; x++)
  {
    if (surface[y][x] > max)
      max = surface[y][x];

    if (surface[y][x] < min)
      min = surface[y][x];
  }

  float k = (1.0)/(max - min);
  float q = 1.0 -k*max;

  for (unsigned int y = 0; y < height; y++)
  for (unsigned int x = 0; x < width; x++)
    surface[y][x] = k*surface[y][x] + q;
}
