#ifndef _PERLIN_NOISE_H_
#define _PERLIN_NOISE_H_

#include <stdint.h>


class PerlinNoise
{
  private:
    float amp_decay;
    int octaves;
    unsigned int seed;

  public:
    PerlinNoise(float amp_decay = 0.9, int octaves = 16, unsigned int seed = 0);
    virtual ~PerlinNoise();

    void init(float amp_decay = 0.9, int octaves = 16, unsigned int seed = 0);


    float get(float x, float y);

  private:
    int noise2(int x, int y);
    float lin_inter(float x, float y, float s);
    float smooth_inter(float x, float y, float s);
    float noise2d(float x, float y);
};

#endif
