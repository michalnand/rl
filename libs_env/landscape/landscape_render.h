#ifndef _LANDSCAPE_RENDER_H_
#define _LANDSCAPE_RENDER_H_

#include <vector>
#include <image_load.h>
#include "visualisation/glvisualisation.h"


struct sRGB
{
  float r, g, b;
};


class LandscapeRender
{
  private:
    unsigned int width, height, details;

    std::vector<float> height_limits;
    std::vector<std::vector<float>> textures;

  private:
    GLVisualisation visualisation;

  public:
    LandscapeRender();
    virtual ~LandscapeRender();

    void init(unsigned int width, unsigned int height,  std::string config_file);
    void render(std::vector<std::vector<float>> &surface);

  private:

    sRGB get_terrain_color(unsigned int x, unsigned int y, float surface_value);
    sRGB texture_point(unsigned int x, unsigned int y, float surface_value, std::vector<float> &ta, std::vector<float> &tb);

    float vposx(float x);
    float vposy(float y);

    unsigned int get_texture_idx(unsigned int x, unsigned int y, unsigned ch);

};


#endif
