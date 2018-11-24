#include "env_stack.h"

#include <math.h>
#include <iomanip>
#include <iostream>
#include <sstream>

EnvStack::EnvStack( unsigned int width,
                    unsigned int height)
            :Env()
{
  this->width  = width;
  this->height = height;

  redner_iteration = 0.0;

  reset();
}



EnvStack::EnvStack(EnvStack& other)
            :Env(other)
{
  copy_stack(other);
}

EnvStack::EnvStack(const EnvStack& other)
            :Env(other)
{
  copy_stack(other);
}

EnvStack::~EnvStack()
{

}

EnvStack& EnvStack::operator= (EnvStack& other)
{
  Env::copy(other);
  copy_stack(other);

  return *this;
}

EnvStack& EnvStack::operator= (const EnvStack& other)
{
  Env::copy(other);
  copy_stack(other);

  return *this;
}

void EnvStack::copy_stack(EnvStack& other)
{
  (void)other;
}

void EnvStack::copy_stack(const EnvStack& other)
{
  (void)other;
}


void EnvStack::action(unsigned int action_id)
{
  unsigned int last = items.size()-1;

  float overlap = get_overlap();

  m_reward = 0.0;
  if (action_id == 1)
  {
    items[last]->process(action_id);

    if (overlap > 0.9)
      m_reward = 1.0;
    else
      m_reward = -1.0;

    if (items.size() > 500)
      reset();
    else
      items.push_back(new StackItem(items[last]));
  }

  for (unsigned int i = 0; i < items.size(); i++)
    items[i]->process(0);

  process_step();

  update_state();
}

void EnvStack::print()
{
  std::cout << "socre " << score() << "\n";
  m_state.print();
}

void EnvStack::render()
{
  visualisation.start();

  // angle = angle + 1.0;
  redner_iteration+= 1.0;

  unsigned int view_count = 50;
  for (unsigned int i = 0; i < items.size(); i++)
    if ((items.size() < view_count) || (i > (items.size()-view_count)))
      draw_item(i);

  std::stringstream stream;

  stream << std::fixed << std::setprecision(2) << score();

  std::string str_score;

  str_score+= "score : ";
  str_score+= stream.str();

  str_score+= "    height : " + std::to_string(items.size());

  visualisation.set_color(1.0, 1.0, 1.0);
  visualisation.print(-1.0, -1.0, -3.0, str_score);

  visualisation.finish();
}

void EnvStack::draw_item(unsigned int idx)
{
  float cube_size = 0.06;

  int height = items[idx]->values.size();
  int width  = items[idx]->values[0].size();

  visualisation.push();

  float x_ofs = 0.0;
  float y_ofs = -0.5*cube_size*(items.size() - idx) + 0.3;
  float z_ofs = -4.0;

  int steps = 100;

  visualisation.translate(x_ofs, y_ofs, z_ofs);

  visualisation.rotate(40.0, 45.0 + sin(redner_iteration*0.01)*20, 0.0);


  for (int j = 0; j < height; j++)
    for (int i = 0; i < width; i++)
    {
      if (items[idx]->values[j][i] > 0.0)
      {
        visualisation.push();
        float br = 0.5;

        if (items[idx]->values[j][i] > 0.999)
          br = 1.0;

        float x = (i - width/2.0)*1.2*cube_size;
        float y = 0.0;
        float z = -(j - height/2.0)*1.2*cube_size;



        float phase = (2.0*3.141592654*(idx%steps))/steps;

        float r = sin(phase + 0.0*2.0*3.141592654);
        float g = sin(phase + 0.3333*2.0*3.141592654);
        float b = sin(phase + 0.6666*2.0*3.141592654);

        visualisation.set_color(br*r, br*g, br*b);

        visualisation.translate(x, y, z);
        visualisation.paint_cube(cube_size);

        visualisation.pop();
      }
    }

  visualisation.pop();
}


void EnvStack::reset()
{
  for (unsigned int i = 0; i < items.size(); i++)
    delete items[i];
  items.clear();

  this->item_width  = width*0.3 + 1;
  this->item_height = height*0.3 + 1;

  items.push_back(new StackItem(width, height, item_width, item_height));
  items.push_back(new StackItem(items[0]));

  m_score = 0.0;
  m_state.init(width, height, 2);

  m_actions_count = 2;

  update_state();
}

void EnvStack::update_state()
{
  unsigned int last = items.size()-1;

  m_state.clear();

  for (unsigned int j = 0; j < height; j++)
    for (unsigned int i = 0; i < width; i++)
    {
      if (items[last]->values[j][i] > 0.0)
        m_state.set_element(1.0, i, j, 0);
    }

  for (unsigned int j = 0; j < height; j++)
    for (unsigned int i = 0; i < width; i++)
    {
      if (items[last-1]->values[j][i] > 0.0)
        m_state.set_element(1.0, i, j, 1);
    }
}


float EnvStack::get_overlap()
{
  unsigned int last = items.size()-1;
  return items[last]->compute_overlap();
}
