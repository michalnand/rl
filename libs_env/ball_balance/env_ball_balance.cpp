#include "env_ball_balance.h"

#include <iostream>

#include <math.h>


EnvBallBalance::EnvBallBalance(unsigned int size)
              :Env()
{
  m_actions_count = 5;

  this->size  = size;

  reset();

  m_state.init(this->size, this->size, 2);
}

EnvBallBalance::EnvBallBalance(EnvBallBalance& other)
              :Env(other)
{
  copy_ball_balance(other);
}

EnvBallBalance::EnvBallBalance(const EnvBallBalance& other)
              :Env(other)
{
  copy_ball_balance(other);
}

EnvBallBalance::~EnvBallBalance()
{

}

EnvBallBalance& EnvBallBalance::operator= (EnvBallBalance& other)
{
  copy(other);
  copy_ball_balance(other);

  return *this;
}

EnvBallBalance& EnvBallBalance::operator= (const EnvBallBalance& other)
{
  copy(other);
  copy_ball_balance(other);

  return *this;
}

void EnvBallBalance::copy_ball_balance(EnvBallBalance& other)
{
  size              = other.size;

  dt              = other.dt;
  board_inertia   = other.board_inertia;
  ball_mass       = other.ball_mass;
  friction        = other.friction;

  angle_x         = other.angle_x;
  angle_y         = other.angle_y;
  vx              = other.vx;
  vy              = other.vy;
  x               = other.x;
  y               = other.y;
}

void EnvBallBalance::copy_ball_balance(const EnvBallBalance& other)
{
  size              = other.size;

  dt              = other.dt;
  board_inertia   = other.board_inertia;
  ball_mass       = other.ball_mass;
  friction        = other.friction;

  angle_x         = other.angle_x;
  angle_y         = other.angle_y;
  vx              = other.vx;
  vy              = other.vy;
  x               = other.x;
  y               = other.y;
}


void EnvBallBalance::action(unsigned int action_id)
{
  float r_angle_x = 0;
  float r_angle_y = 0;

  float angle = 20.0*3.141592654*2.0/360.0;

  switch(action_id)
  {
    case 0: r_angle_x = 0.0; r_angle_y = 0.0; break;
    case 1: r_angle_y = angle; break;
    case 2: r_angle_y = -angle; break;
    case 3: r_angle_x = angle; break;
    case 4: r_angle_x = -angle; break;
  }

  process_move(r_angle_x, r_angle_y);

  float r = sqrt(x*x + y*y);

  m_reward  = 0.0;
  m_done    = false;

  if ((fabs(x) > 1.0)||(fabs(y) > 1.0))
  {
    m_reward = -1.0;
    reset();
    m_done = true;
  }
  else
  if (r < target_radius)
  {
    m_reward = 1.0;
    reset();
    m_done = true;
  }
  else
  {
    float dist = sqrt(x*x + y*y)/sqrt(2.0);
    m_reward = -dist*0.5;
  }

  process_step();
  update_state();
}

void EnvBallBalance::print()
{
  std::cout << "score = " << m_score << "\n";
  m_state.print();
}

void EnvBallBalance::render()
{
  float angle_y_ = -angle_y*0.7*360.0/(2.0*3.141592654);
  float angle_x_ =  angle_x*0.7*360.0/(2.0*3.141592654);

  visualisation.start();

  int i_score = round(m_score);

  std::string score;
  score = "score = " + std::to_string(i_score);
  visualisation.push();
  visualisation.set_color(1.0, 1.0, 1.0);
  visualisation.print(-0.2, 0.9, -3.0, score);
  visualisation.pop();

  visualisation.push();

  visualisation.translate(0.0, 0.0, -3.0);
  visualisation.rotate(-45.0 + angle_y_, 0.0 + angle_x_, 0.0);


  float element_size = 1.8/size;
  float sphere_size = 2.0*element_size;

  float surface_radius = 2.0;

  for (int y = 0; y < size; y++)
  for (int x = 0; x < size; x++)
  {
    float x_ = vpos(x);
    float y_ = vpos(y);
    float z_ = -(surface_radius - sqrt(surface_radius*surface_radius - x_*x_ - y_*y_))*0.5;
    visualisation.push();

    if (sqrt(x_*x_ + y_*y_) <= sphere_size)
      visualisation.set_color(0.7, 0.7, 0.0);
    else
      visualisation.set_color(0.3, 0.3, 0.3);

    visualisation.translate(vpos(x), vpos(y), z_);


    visualisation.paint_square(element_size);
    visualisation.pop();
  }

  float z_ = -(surface_radius - sqrt(surface_radius*surface_radius - x*x - y*y))*0.5;

  visualisation.push();
  visualisation.translate(x, y, z_ + 2.0*element_size);
  visualisation.set_color(0.9, 0.9, 0.9);
  visualisation.paint_sphere(2.0*element_size);
  visualisation.pop();




  visualisation.pop();

  visualisation.finish();
}



void EnvBallBalance::reset()
{
  target_radius = 0.2;

  dt            = 0.05;
  board_inertia = 0.95;
  ball_mass     = 0.1;
  friction      = 0.2;

  angle_x       = 0.0;
  angle_y       = 0.0;
  vx            = 0.0;
  vy            = 0.0;

  x = rnd(0.5, 0.9);
  y = rnd(0.5, 0.9);

  if (rand()%2)
    x*= -1.0;

  if (rand()%2)
    y*= -1.0;

  x_1 = x;
  y_1 = y;
  x_2 = x;
  y_2 = y;
  x_3 = x;
  y_3 = y;
}

void EnvBallBalance::process_move(float r_angle_x, float r_angle_y)
{
  angle_x = board_inertia*angle_x + (1.0 - board_inertia)*r_angle_x;
  angle_y = board_inertia*angle_y + (1.0 - board_inertia)*r_angle_y;

  float fg = 9.80665*ball_mass;

  float fx = fg*sin(angle_x);
  float fy = fg*sin(angle_y);

  float f_friction_x = -vx*friction;
  float f_friction_y = -vy*friction;

  float k = 0.005;
  float f_centrifugal_x = -k*(0.0 - x);
  float f_centrifugal_y = -k*(0.0 - y);

  float ax = (fx + f_friction_x + f_centrifugal_x)/ball_mass;
  float ay = (fy + f_friction_y + f_centrifugal_y)/ball_mass;

  vx = vx + ax*dt;
  vy = vy + ay*dt;

  x_3 = x_2;
  y_3 = y_2;
  x_2 = x_1;
  y_2 = y_1;
  x_1 = x;
  y_1 = y;

  x  = x  + vx*dt;
  y  = y  + vy*dt;


}


void EnvBallBalance::update_state()
{
  m_state.clear();

  float k = 20.0;

  for (int y = 0; y < size; y++)
  for (int x = 0; x < size; x++)
  {
    float x_ = (x*1.0/size - 0.5)*2.0;
    float y_ = (y*1.0/size - 0.5)*2.0;

    float dist = 0.0;
    dist+= pow(this->x - x_, 2.0);
    dist+= pow(this->y - y_, 2.0);
    dist = exp(-k*dist);

    if (dist < 0.01)
      dist = 0.0;

    m_state.set_element(dist, x, y, 0);
  }


  for (int y = 0; y < size; y++)
  for (int x = 0; x < size; x++)
  {
    float x_ = (x*1.0/size - 0.5)*2.0;
    float y_ = (y*1.0/size - 0.5)*2.0;

    float dist = 0.0;
    dist+= pow(this->x_3 - x_, 2.0);
    dist+= pow(this->y_3 - y_, 2.0);
    dist = exp(-k*dist);

    if (dist < 0.01)
      dist = 0.0;

    m_state.set_element(dist, x, y, 1);
  }

  m_state.normalise();

}


float EnvBallBalance::vpos(float pos)
{
  return 2.0*((pos*1.0/size) - 0.5);
}

float EnvBallBalance::rnd(float min, float max)
{
  float result = (rand()%1000000)/1000000.0;

  result = result*(max - min) + min;

  return result;
}

int EnvBallBalance::get_key()
{
  return visualisation.get_key();
}
