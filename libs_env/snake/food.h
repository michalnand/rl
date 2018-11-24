#ifndef _FOOD_H_
#define _FOOD_H_

#include <visualisation/glvisualisation.h>
#include <vector>

class Food
{
  private:
    std::vector<float> pos_x;
    std::vector<float> pos_y;
    std::vector<bool>  active;

    GLVisualisation *visualisation;

    unsigned int sensors_count;
    float food_size;

  public:
    // Default constructor
    Food();

    // Copy constructor
    Food(Food& other);

    // Copy constructor
    Food(const Food& other);

    // Destructor
    virtual ~Food();

    // Copy assignment operator
    Food& operator= (Food& other);

    // Copy assignment operator
    Food& operator= (const Food& other);

  protected:
    void copy(Food& other);
    void copy(const Food& other);

  public:
    void init(unsigned int sensors_count, GLVisualisation &visualisation);
    float eat(float x, float y);
    void render();

    std::vector<float> state(float x, float y, float theta_ofs);

  private:
    float rnd();
    void init_food();
    unsigned int nearest_food(float x, float y);


};


#endif
