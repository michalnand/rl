#include "food.h"

#include <math.h>

Food::Food()
{

}

Food::Food(Food& other)
{
  copy(other);
}

Food::Food(const Food& other)
{
  copy(other);
}

Food::~Food()
{

}

Food& Food::operator= (Food& other)
{
  copy(other);

  return *this;
}

Food& Food::operator= (const Food& other)
{
  copy(other);

  return *this;
}

void Food::copy(Food& other)
{
  (void)other;
  //TODO copy other to this
}

void Food::copy(const Food& other)
{
  (void)other;
  //TODO copy other to this
}




void Food::init(unsigned int sensors_count, GLVisualisation &visualisation)
{
  this->visualisation = &visualisation;

  unsigned int count = 100;
  active.resize(count);
  pos_x.resize(count);
  pos_y.resize(count);

  food_size = 0.02;

  this->sensors_count = sensors_count;
  init_food();
}


float Food::eat(float x, float y)
{
  float result = 0.0;

  for (unsigned int i = 0; i < active.size(); i++)
    if (active[i] == true)
    {
      float dist = 0.0;
      dist+= (pos_x[i] - x)*(pos_x[i] - x);
      dist+= (pos_y[i] - y)*(pos_y[i] - y);
      dist = sqrt(dist);
      if (dist < 0.05)
      {
        result+= 1.0;
        active[i] = 0;
      }
    }

  unsigned int eaten = 0;
  for (unsigned int i = 0; i < active.size(); i++)
    if (active[i] == false)
        eaten++;

  if (eaten > active.size()*0.9)
    init_food();


  return result;
}

void Food::render()
{
  for (unsigned int i = 0; i < active.size(); i++)
  if (active[i] == true)
  {
    visualisation->push();
    visualisation->set_color(1.0, 0.5, 0.0);

    // visualisation->rotate(0.0, 0.0, -m_theta*360.0/3.141592654);
    visualisation->translate(pos_x[i], pos_y[i], -3.0);

    visualisation->paint_square(food_size);

    visualisation->pop();
  }
}


float Food::rnd()
{
  float v = (rand()%1000000)/1000000.0;
  if (rand()%2)
    v*= -1.0;

  return v;
}

void Food::init_food()
{
  float range = 0.7;

  float x = rnd()*range;
  float y = rnd()*range;
  for (unsigned int i = 0; i < active.size(); i++)
  {
    float r = fabs(rnd()*0.3);
    float theta = rnd()*2.0*3.141592645;

    active[i] = true;
    pos_x[i] = x  + r*cos(theta);
    pos_y[i] = y  + r*sin(theta);
  }
}




std::vector<float> Food::state(float x, float y, float theta_ofs)
{
  std::vector<float> result;
  result.resize(sensors_count);

  float r = food_size*0.1;

  for (unsigned int i = 0; i < sensors_count; i++)
  {
    float theta = theta_ofs + (3.141592654*i)/sensors_count;
    float x_pos = x + r*cos(theta);
    float y_pos = y + r*sin(theta);

    unsigned int idx = nearest_food(x_pos, y_pos);

    float distance = 0.0;
    distance+= (x_pos - pos_x[idx])*(x_pos - pos_x[idx]);
    distance+= (y_pos - pos_y[idx])*(y_pos - pos_y[idx]);

    result[i] = sqrt(distance);
  }


  float max = result[0];
  float min = result[0];

  for (unsigned int i = 0; i < result.size(); i++)
  {
    if (result[i] > max)
      max = result[i];
    if (result[i] < min)
      min = result[i];
  }

  float k = 0.0;
  float q = 0.0;
  if (max > min)
  {
    k = (1.0 - 0.0)/(max - min);
    q = 1.0 - k*max;
  }


  for (unsigned int i = 0; i < result.size(); i++)
  {
    result[i] = k*result[i] + q;
  }

  return result;
}


unsigned int Food::nearest_food(float x, float y)
{
  float dist_min = 1000000000.0;
  unsigned int result = 0;

  for (unsigned int i = 0; i < active.size(); i++)
    if (active[i])
  {
    float distance = 0.0;
    distance+= (pos_x[i] - x)*(pos_x[i] - x);
    distance+= (pos_y[i] - y)*(pos_y[i] - y);
    distance = sqrt(distance);

    if (distance < dist_min)
    {
      dist_min = distance;
      result = i;
    }
  }

  return result;
}
