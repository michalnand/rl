#include "env_pacman.h"

#include <iostream>
#include <json_config.h>

EnvPacman::EnvPacman(std::string config_file_name)
              :Env()
{
  json.load(config_file_name);
  m_actions_count = 4;


  init_game(json.result);
}


EnvPacman::EnvPacman(EnvPacman& other)
              :Env(other)
{
  copy_pacman(other);
}

EnvPacman::EnvPacman(const EnvPacman& other)
              :Env(other)
{
  copy_pacman(other);
}

EnvPacman::~EnvPacman()
{

}

EnvPacman& EnvPacman::operator= (EnvPacman& other)
{
  copy(other);
  copy_pacman(other);

  return *this;
}

EnvPacman& EnvPacman::operator= (const EnvPacman& other)
{
  copy(other);
  copy_pacman(other);

  return *this;
}

void EnvPacman::copy_pacman(EnvPacman& other)
{
  (void)other;
}

void EnvPacman::copy_pacman(const EnvPacman& other)
{
  (void)other;
}



void EnvPacman::action(unsigned int action_id)
{
  action_id = rand()%4;

  m_reward = 0.0;
  m_done   = false;

  for (unsigned int i = 0; i < player_position.size(); i++)
  {
    switch (action_id)
    {
      case 0: move_right(player_position[i]); break;
      case 1: move_left(player_position[i]);  break;
      case 2: move_up(player_position[i]);    break;
      case 3: move_down(player_position[i]);  break;
    }

    unsigned int sprite = grid[player_position[i].y][player_position[i].x];
    unsigned int sprite_idx = sprites_mapped[sprite];

    if (sprites[sprite_idx].get().name == "food")
    {
      grid[player_position[i].y][player_position[i].x] = 0;
      m_reward = 0.5;
    }
  }

  for (unsigned int i = 0; i < enemy_position.size(); i++)
  {
    process_enemy_move(enemy_position[i], enemy_state[i]);
  }

  unsigned int food_cnt = 0;
  for (unsigned int y = 0; y < height; y++)
  for (unsigned int x = 0; x < width; x++)
  {
    unsigned int sprite = grid[y][x];
    unsigned int sprite_idx = sprites_mapped[sprite];

    if (sprites[sprite_idx].get().name == "food")
    {
      food_cnt++;
    }
  }


  if (food_cnt == 0)
  {
    m_reward = 1.0;
    m_done   = true;
    game_reset();
  }
  else
  {
    for (unsigned int i = 0; i < player_position.size(); i++)
      for (unsigned int j = 0; j < enemy_position.size(); j++)
      {
        if ( (player_position[i].x == enemy_position[j].x) &&
             (player_position[i].y == enemy_position[j].y) )
        {
          m_reward = -1.0;
          m_done = true;
          player_reset();
        }
      }
  }

  process_step();
  update_state();
}


int EnvPacman::is_cross_road(sPosition &position)
{
  int result = 0;

  if ((position.x+1) < (int)width)
  {
    unsigned int element    = grid[position.y][position.x+1];
    unsigned int sprite_idx = sprites_mapped[element];
    if (sprites[sprite_idx].get().solid == false)
      result++;
  }

  if ((position.x-1) >= 0)
  {
    unsigned int element    = grid[position.y][position.x-1];
    unsigned int sprite_idx = sprites_mapped[element];
    if (sprites[sprite_idx].get().solid == false)
      result++;
  }

  if ((position.y+1) < (int)height)
  {
    unsigned int element    = grid[position.y+1][position.x];
    unsigned int sprite_idx = sprites_mapped[element];
    if (sprites[sprite_idx].get().solid == false)
      result++;
  }

  if ((position.y-1) >= 0)
  {
    unsigned int element    = grid[position.y-1][position.x];
    unsigned int sprite_idx = sprites_mapped[element];
    if (sprites[sprite_idx].get().solid == false)
      result++;
  }

  return result;
}

void EnvPacman::process_enemy_move(sPosition &position, int &state)
{
  if (is_cross_road(position) == 4)
  {
    switch (rand()%4)
    {
      case 0: move_right(position);
              break;

      case 1: move_up(position);
              break;

      case 2: move_left(position);
              break;

      case 3: move_down(position);
              break;
    }
  }
  else
  {
    switch (state)
    {
      case 0: if (move_right(position) == false)
                state = 1;
              break;

      case 1: if (move_up(position) == false)
                state = 2;
              break;

      case 2: if (move_left(position) == false)
                state = 3;
              break;

      case 3: if (move_down(position) == false)
                state = 0;
              break;
    }
  }
}

void EnvPacman::print()
{
  std::cout << "score = " << m_score << "\n";
//  m_state.print();
}

void EnvPacman::render()
{
  visualisation.start();
  visualisation.translate(0.0, 0.0, -3.0);

  visualisation.push();

  unsigned int size = height;
  if (width > size)
    size = width;

  float element_size = 1.8/size;

  for (int y = 0; y < (int)height; y++)
  for (int x = 0; x < (int)width; x++)
  {
    visualisation.push();
    visualisation.translate(vposx(x), vposy(y), 0.0);

    unsigned int element = grid[y][x];
    unsigned int sprite_idx = sprites_mapped[element];

    sprites[sprite_idx].render(visualisation, element_size);

    visualisation.pop();
  }

  for (unsigned int i = 0; i < player_position.size(); i++)
  {
    visualisation.push();
    visualisation.translate(vposx(player_position[i].x), vposy(player_position[i].y), 0.002);

    unsigned int element    = 3;
    unsigned int sprite_idx = sprites_mapped[element];

    sprites[sprite_idx].render(visualisation, element_size);

    visualisation.pop();
  }



  for (unsigned int i = 0; i < enemy_position.size(); i++)
  {
    visualisation.push();
    visualisation.translate(vposx(enemy_position[i].x), vposy(enemy_position[i].y), 0.001);

    unsigned int element    = 4;
    unsigned int sprite_idx = sprites_mapped[element];

    sprites[sprite_idx].render(visualisation, element_size);

    visualisation.pop();
  }



  std::string score;
  score = "score = " + std::to_string(m_score);
  visualisation.push();
  visualisation.set_color(1.0, 1.0, 1.0);
  visualisation.print(-0.2, 0.9, 0.0, score);
  visualisation.pop();

  visualisation.pop();
  visualisation.finish();
}

void EnvPacman::update_state()
{
  m_state.clear();

  for (int y = 0; y < (int)height; y++)
  for (int x = 0; x < (int)width; x++)
  {
    unsigned int element = grid[y][x];
    m_state.set_element(1.0, x, y, element);
  }

  for (unsigned int i = 0; i < player_position.size(); i++)
  {
    unsigned int element = 3;
    m_state.set_element(1.0, player_position[i].x, player_position[i].y, element);
  }

  for (unsigned int i = 0; i < enemy_position.size(); i++)
  {
    unsigned int element = 4;
    m_state.set_element(1.0, enemy_position[i].x, enemy_position[i].y, element);
  }

}



void EnvPacman::init_game(Json::Value &json)
{
  sprites.clear();
  for (unsigned int i = 0; i < json["sprites"].size(); i++)
    sprites.push_back(Sprite(json["sprites"][i]));

  sprites_mapped.clear();
  for (unsigned int i = 0; i < sprites.size(); i++)
    sprites_mapped[sprites[i].get().id] = i;

  /*
  for (unsigned int i = 0; i < sprites.size(); i++)
    std::cout << "sprite name " << sprites[i].get().name << " " << sprites[i].get().id << "\n";
  */

  player_position.clear();
  for (unsigned int i = 0; i < json["player_position"].size(); i++)
  {
    sPosition position;
    position.x = json["player_position"][i][0].asInt();
    position.y = json["player_position"][i][1].asInt();
    position.z = 0;
    player_position.push_back(position);
  }

  enemy_position.clear();
  enemy_state.clear();
  for (unsigned int i = 0; i < json["enemy_position"].size(); i++)
  {
    sPosition position;
    position.x = json["enemy_position"][i][0].asInt();
    position.y = json["enemy_position"][i][1].asInt();
    position.z = 0;
    enemy_position.push_back(position);
    enemy_state.push_back(i%4);
  }



  width  = json["grid"][0].size();
  height = json["grid"].size();

  grid.resize(height);
  for (unsigned int j = 0; j < height; j++)
    grid[j].resize(width);

  for (unsigned int j = 0; j < height; j++)
    for (unsigned int i = 0; i < width; i++)
      grid[j][i] = json["grid"][j][i].asInt();

  m_state.init(width, height, sprites.size());
}

void EnvPacman::game_reset()
{
  player_reset();

  for (unsigned int j = 0; j < height; j++)
    for (unsigned int i = 0; i < width; i++)
      grid[j][i] = json.result["grid"][j][i].asInt();
}

void EnvPacman::player_reset()
{
  player_position.clear();
  for (unsigned int i = 0; i < json.result["player_position"].size(); i++)
  {
    sPosition position;
    position.x = json.result["player_position"][i][0].asInt();
    position.y = json.result["player_position"][i][1].asInt();
    position.z = 0;
    player_position.push_back(position);
    printf("%u %u\n", position.x, position.y);
  }
}

float EnvPacman::vposx(int x)
{
  return x*2.0/width - 1.0;
}

float EnvPacman::vposy(int y)
{
  return -(y*2.0/height - 1.0);
}

bool EnvPacman::move_right(sPosition &position)
{
  if ((position.x+1) < (int)width)
  {
    unsigned int element    = grid[position.y][position.x+1];
    unsigned int sprite_idx = sprites_mapped[element];
    if (sprites[sprite_idx].get().solid == false)
    {
      position.x+= 1;
      return true;
    }
  }

  return false;
}

bool EnvPacman::move_left(sPosition &position)
{
  if ((position.x-1) >= 0)
  {
    unsigned int element    = grid[position.y][position.x-1];
    unsigned int sprite_idx = sprites_mapped[element];
    if (sprites[sprite_idx].get().solid == false)
    {
      position.x-= 1;
      return true;
    }
  }

  return false;
}

bool EnvPacman::move_up(sPosition &position)
{
  if ((position.y+1) < (int)height)
  {
    unsigned int element    = grid[position.y+1][position.x];
    unsigned int sprite_idx = sprites_mapped[element];
    if (sprites[sprite_idx].get().solid == false)
    {
      position.y+= 1;
      return true;
    }
  }

  return false;
}

bool EnvPacman::move_down(sPosition &position)
{
  if ((position.y-1) >= 0)
  {
    unsigned int element    = grid[position.y-1][position.x];
    unsigned int sprite_idx = sprites_mapped[element];
    if (sprites[sprite_idx].get().solid == false)
    {
      position.y-= 1;
      return true;
    }
  }

  return false;
}
