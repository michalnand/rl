#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include "env.h"
#include "perlin_noise.h"

#include "landscape_render.h"


class EnvLandscape: public Env
{
    protected:
      PerlinNoise noise;

      unsigned int width, height;

      std::vector<std::vector<float>> surface;

      LandscapeRender landscape_render;

    public:
      // Default constructor
      EnvLandscape();

      // Copy constructor
      EnvLandscape(EnvLandscape& other);

      // Copy constructor
      EnvLandscape(const EnvLandscape& other);

      // Destructor
      virtual ~EnvLandscape();

      // Copy assignment operator
      EnvLandscape& operator= (EnvLandscape& other);

      // Copy assignment operator
      EnvLandscape& operator= (const EnvLandscape& other);

    protected:
      void copy_blackbox(EnvLandscape& other);
      void copy_blackbox(const EnvLandscape& other);

    public:
      void render();

    protected:
      void generate();
      void normalise();

};



#endif
