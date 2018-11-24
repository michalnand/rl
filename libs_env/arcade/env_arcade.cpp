#include "env_arcade.h"

#include <iostream>


EnvArcade::EnvArcade(unsigned int width, unsigned int height)
              :Env()
{
  m_actions_count = 3;

  this->width   = width;
  this->height  = height;

  player_y = 0;
  player_state = PLAYER_STATE_INIT;

  screen.init(width, height);

  obstacles.resize(3);

  for (unsigned int i = 0; i < obstacles.size(); i++)
  {
    unsigned int x = ((rand()%width) + width)/2;
    unsigned int y = rand()%height;
    unsigned int max_width = 5;
    unsigned int max_height = 5;
    obstacles[i].create(x, y, max_width, max_height, AF_OBSTACLE);
  }


  m_state.init(this->width, this->height, 3);
}

EnvArcade::EnvArcade(EnvArcade& other)
              :Env(other)
{
  copy_arcade(other);
}

EnvArcade::EnvArcade(const EnvArcade& other)
              :Env(other)
{
  copy_arcade(other);
}

EnvArcade::~EnvArcade()
{

}

EnvArcade& EnvArcade::operator= (EnvArcade& other)
{
  copy(other);
  copy_arcade(other);

  return *this;
}

EnvArcade& EnvArcade::operator= (const EnvArcade& other)
{
  copy(other);
  copy_arcade(other);

  return *this;
}

void EnvArcade::copy_arcade(EnvArcade& other)
{
  width   = other.width;
  height  = other.height;
  screen  = other.screen;
}

void EnvArcade::copy_arcade(const EnvArcade& other)
{
  width   = other.width;
  height  = other.height;
  screen  = other.screen;
}


void EnvArcade::action(unsigned int action_id)
{
  screen.clear();

  for (unsigned int i = 0; i < obstacles.size(); i++)
    obstacles[i].move(-1, 0);


  for (unsigned int i = 0; i < obstacles.size(); i++)
    if (obstacles[i].is_out(screen))
    {
      unsigned int x = ((rand()%width) + width)/2;
      unsigned int y = rand()%height;
      unsigned int max_width  = width/8;
      unsigned int max_height = height/8;

      AracadeField field = AF_COMMON;

      if ((rand()%100) < 30)
        field = AF_POINT;
      else
        field = AF_OBSTACLE;


      obstacles[i].create(x, y, max_width, max_height, field);
    }

  for (unsigned int i = 0; i < obstacles.size(); i++)
    obstacles[i].add_to_screen(screen);

  /*
  switch (player_state)
  {
    case PLAYER_STATE_INIT    :
                                if (action_id == 1)
                                {
                                  player_state = PLAYER_STATE_JUMPING;
                                }
                                break;

    case PLAYER_STATE_JUMPING :
                                if (player_y < (height-1))
                                  player_y++;
                                else
                                  player_state = PLAYER_STATE_FALLING;
                                break;

    case PLAYER_STATE_FALLING : if (player_y > 0)
                                  player_y--;
                                else
                                  player_state = PLAYER_STATE_INIT;
                                break;
  }
  */

  action_id = rand()%3;
  switch (action_id)
  {
    case 0: break;

    case 1: if (player_y < (height-1))
                player_y++;
            break;

    case 2: if (player_y > 0)
                player_y--;
            break;
  }


  screen.set(0, player_y, AF_PLAYER);

  m_reward = 0.0;

  for (unsigned int i = 0; i < obstacles.size(); i++)
    if (obstacles[i].is_colission(0, player_y))
    {
      if (obstacles[i].get_type() == AF_OBSTACLE)
        m_reward = -1.0;
      if (obstacles[i].get_type() == AF_POINT)
        m_reward =  1.0;
    }

  m_done = false;
  if (m_reward < 0.0)
    m_done = true;

  process_step();
  update_state();
}

void EnvArcade::print()
{
  std::cout << "score = " << m_score << "\n";

  // m_state.print();
}

void EnvArcade::render()
{
  visualisation.start();

    visualisation.translate(0.0, 0.0, -3.0);
    screen.render(visualisation);


    std::string score;
    score = "score = " + std::to_string(m_score);
    visualisation.push();
    visualisation.set_color(1.0, 1.0, 1.0);
    visualisation.print(-0.2, 1.1, 0.0, score);
    visualisation.pop();


  visualisation.finish();
}

void EnvArcade::update_state()
{
  m_state.clear();

  for (unsigned int y = 0; y < height; y++)
  for (unsigned int x = 0; x < width; x++)
  {
    sArcadeFieldColor color = screen.get_color(x, y);

    m_state.set_element(color.r, x, y, 0);
    m_state.set_element(color.g, x, y, 1);
    m_state.set_element(color.b, x, y, 2);
  }
}
