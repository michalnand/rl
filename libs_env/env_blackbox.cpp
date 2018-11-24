#include "env_blackbox.h"

#include <svg.h>
#include <iostream>
#include <math.h>


EnvBlackBox::EnvBlackBox()
            :Env()
{

}

EnvBlackBox::EnvBlackBox(std::string config_file_name)
            :Env()
{
  load(config_file_name);
}


EnvBlackBox::EnvBlackBox(EnvBlackBox& other)
            :Env(other)
{
  copy_blackbox(other);
}

EnvBlackBox::EnvBlackBox(const EnvBlackBox& other)
            :Env(other)
{
  copy_blackbox(other);
}

EnvBlackBox::~EnvBlackBox()
{

}

EnvBlackBox& EnvBlackBox::operator= (EnvBlackBox& other)
{
  copy_blackbox(other);

  return *this;
}

EnvBlackBox& EnvBlackBox::operator= (const EnvBlackBox& other)
{
  copy_blackbox(other);

  return *this;
}

void EnvBlackBox::copy_blackbox(EnvBlackBox& other)
{
  states = other.states;
}

void EnvBlackBox::copy_blackbox(const EnvBlackBox& other)
{
  states = other.states;
}



void EnvBlackBox::create(std::string result_file_prefix, std::string config_file_name)
{
  (void)result_file_prefix;
  
  JsonConfig json(config_file_name);

  unsigned int amplitude_decay = json.result["noise"]["amplitude_decay"].asFloat();
  unsigned int octaves         = json.result["noise"]["octaves"].asInt();
  unsigned int seed            = json.result["noise"]["seed"].asInt();

  noise.init(amplitude_decay, octaves, seed);



  unsigned int states_count     = json.result["states_count"].asInt();
  unsigned int actions_count    = json.result["actions_count"].asInt();
  state_size       = json.result["state_size"].asInt();

  area_size        = json.result["area_size"].asInt();

  float max = -10000000.0;
  float min = -max;


  for (unsigned int j = 0; j < states_count; j++)
  {
    unsigned int size_half = state_size/2 + 1;

    float x = size_half + rand()%(area_size - 2*size_half);
    float y = size_half + rand()%(area_size - 2*size_half);

    BlackBoxState state(  state_size,
                          actions_count,
                          area_size,
                          x,
                          y,
                          noise );

    if (state.max() > max)
      max = state.max();
    if (state.min() < min)
      min = state.min();

    states.push_back(state);
  }

  for (unsigned int j = 0; j < states_count; j++)
    states[j].normalise(min, max);

  for (unsigned int j = 0; j < states_count; j++)
    states[j].create_reward();

  for (unsigned int j = 0; j < states.size(); j++)
  {
    auto nearest = find_nearest(states[j], states, actions_count);

    std::vector<unsigned int> transition;
    for (unsigned int i = 0; i < nearest.size(); i++)
      transition.push_back(nearest[i]);

    states[j].set_transition(transition);
  }

  m_actions_count = actions_count;

  std::string dirrectory = "my_blackbox/";
  save_image(dirrectory);
}





std::vector<int> EnvBlackBox::find_nearest(BlackBoxState &state, std::vector<BlackBoxState> &other, unsigned int count)
{
  std::vector<int> result;

  for (unsigned int j = 0; j < count; j++)
  {
    float min_d = 1000000000.0;
    int min_idx = -1;

    for (unsigned int i = 0; i < other.size(); i++)
    {
      float d = 0.0;

      d+= pow(state.x() - other[i].x(), 2.0);
      d+= pow(state.y() - other[i].y(), 2.0);

      if ( (d > 0.0) && (d < min_d)  && (is_in(result, i) == false) )
      {
        min_d = d;
        min_idx = i;
      }
    }

    result.push_back(min_idx);
  }

  return result;
}


bool EnvBlackBox::is_in(std::vector<int> &v, int num)
{
  for (unsigned int i = 0; i < v.size(); i++)
    if (v[i] == num)
      return true;

  return false;
}



void EnvBlackBox::save_image(std::string file_name)
{
  SVG svg;
  svg.add_header(area_size, area_size);

  unsigned int images_count = 100;

  for (unsigned int j = 0; j < images_count; j++)
  {
    std::string state_image_file_name = file_name + std::to_string(j) + ".png";
    states[j].save_image_state(state_image_file_name);
  }

  for (unsigned int j = 0; j < images_count; j++)
  {
    std::string state_image_file_name = std::to_string(j) + ".png";

    svg.add_image_link( states[j].x() - state_size/2,
                        states[j].y() - state_size/2,
                        state_size,
                        state_size,
                        state_image_file_name);
  }


  for (unsigned int j = 0; j < states.size(); j++)
  {
    auto transition = states[j].transition();

    for (unsigned int i = 0; i < transition.size(); i++)
    {
      auto next_state = states[transition[i]];

      int x =       states[j].x();
      int y =       states[j].y();
      int x_end =   next_state.x();
      int y_end =   next_state.y();

      svg.add_line( x,
                    y,

                    x_end,
                    y_end,

                    1,

                    0, 0, 0,
                    0, 0, 0);
    }
  }

  for (unsigned int j = 0; j < states.size(); j++)
  {
    int x =       states[j].x();
    int y =       states[j].y();
    int radius =  2 + area_size/8000;


    int r = 50;
    int g = 50;
    int b = 50;

    float reward = states[j].reward();

    if (reward > 0.0)
    {
      r = 255;
      g = 0;
      b = 0;
    }

    if (reward < 0.0)
    {
      r = 0;
      g = 0;
      b = 255;
    }

    svg.add_circle( x,
                  y,

                  radius,

                  1,

                  r, g, b,
                  0, 0, 0);
  }





  svg.add_footer();
  svg.save(file_name + "blackbox.svg");
}



/*


void EnvBlackBox::action(unsigned int action_id)
{
  unsigned int next_state = states[state_idx].transition[action_id];

  m_reward = states[next_state].reward;
  m_score+= m_reward;

  m_state.set(states[next_state].state);

  state_idx = next_state;
}

void EnvBlackBox::print()
{
  std::cout << "score " << m_score << "  reward " << m_reward << "\n";
  m_state.print();
  std::cout << "\n";
}
*/
