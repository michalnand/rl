#include "landscape_render.h"

#include <iostream>
#include <math.h>
#include <json_config.h>

LandscapeRender::LandscapeRender()
{
  width = 0;
  height = 0;
}

LandscapeRender::~LandscapeRender()
{

}

void LandscapeRender::init(unsigned int width, unsigned int height, std::string config_file)
{
  JsonConfig json(config_file);

  this->width   = width;
  this->height  = height;

  this->details = json.result["details"].asInt();
  if (this->details <= 0)
    this->details = 1;


  for (unsigned int j = 0; j < json.result["textures"].size(); j++)
  {
    std::string texture_file_name = json.result["textures"][j].asString();
    std::cout << "loading texture " << texture_file_name << "\n";

    ImageLoad image(texture_file_name, false, true);

    textures.push_back(image.get());
  }

  for (unsigned int j = 0; j < json.result["height_limits"].size(); j++)
  {
    float v = json.result["height_limits"][j].asFloat();
    height_limits.push_back(v);
  }
}


void LandscapeRender::render(std::vector<std::vector<float>> &surface)
{
  visualisation.start();

  visualisation.push();

  visualisation.rotate(-70, 0, 0);
  visualisation.translate(0, 3.0, -1.0);

  unsigned int step_size = details;

  for (unsigned int y = 0; y < (height-step_size); y+= step_size)
  for (unsigned int x = 0; x < (width-step_size); x+= step_size)
  {
    float surface_value_0 = surface[x][y];
    float surface_value_1 = surface[x][y+step_size];
    float surface_value_2 = surface[x+step_size][y+step_size];
    float surface_value_3 = surface[x+step_size][y];

    visualisation.push();

    auto color0 = get_terrain_color(x, y, surface_value_0);
    auto color1 = get_terrain_color(x, y+step_size, surface_value_1);
    auto color2 = get_terrain_color(x+step_size, y+step_size, surface_value_2);
    auto color3 = get_terrain_color(x+step_size, y, surface_value_3);


    color1 = color0;
    color2 = color0;
    color3 = color0;

    visualisation.rotate(0, 0, visualisation.time()*1000);

    float k = 0.5;
    visualisation.paint_quad( vposx(x), vposy(y), surface_value_0*k,                      color0.r, color0.g, color0.b,
                              vposx(x), vposy(y+step_size), surface_value_1*k,            color1.r, color1.g, color1.b,
                              vposx(x+step_size), vposy(y+step_size), surface_value_2*k,  color2.r, color2.g, color2.b,
                              vposx(x+step_size), vposy(y), surface_value_3*k,            color3.r, color3.g, color3.b);

    visualisation.pop();
  }

  visualisation.pop();
  visualisation.finish();
}






sRGB LandscapeRender::get_terrain_color(unsigned int x, unsigned int y, float surface_value)
{
  sRGB result;


  result.r = 1.0;
  result.g = 1.0;
  result.b = 1.0;

  for (unsigned int i = 0; i < textures.size(); i++)
  {
    if (surface_value > height_limits[i])
    {
      result.r = textures[i][get_texture_idx(x, y, 0)];
      result.g = textures[i][get_texture_idx(x, y, 1)];
      result.b = textures[i][get_texture_idx(x, y, 2)];
      break;
    }
  }

  return result;
}


sRGB LandscapeRender::texture_point(unsigned int x, unsigned int y, float surface_value, std::vector<float> &ta, std::vector<float> &tb)
{
  sRGB result;

  result.r = surface_value*ta[get_texture_idx(x, y, 0)];
  result.g = surface_value*ta[get_texture_idx(x, y, 1)];
  result.b = surface_value*ta[get_texture_idx(x, y, 2)];

  result.r+= (1.0 - surface_value)*tb[get_texture_idx(x, y, 0)];
  result.g+= (1.0 - surface_value)*tb[get_texture_idx(x, y, 1)];
  result.b+= (1.0 - surface_value)*tb[get_texture_idx(x, y, 2)];

  return result;
}

unsigned int LandscapeRender::get_texture_idx(unsigned int x, unsigned int y, unsigned ch)
{
  unsigned int texture_size = 256;

  y = y%texture_size;
  y = y%texture_size;
  return (ch*texture_size*texture_size + y*texture_size + x);
}

float LandscapeRender::vposx(float x)
{
  return (x/width - 0.5)*4.0;
}

float LandscapeRender::vposy(float y)
{
  return (y/height - 0.5)*4.0;
}
