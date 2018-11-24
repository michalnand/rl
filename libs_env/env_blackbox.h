#ifndef _BLACKBOX_H_
#define _BLACKBOX_H_

#include "env.h"

#include <json_config.h>
#include "perlin_noise.h"

#include "blackbox_state.h"

class EnvBlackBox: public Env
{
    protected:
      PerlinNoise noise;

      std::vector<BlackBoxState> states;

      unsigned int area_size, state_size;

    public:
      // Default constructor
      EnvBlackBox();
      EnvBlackBox(std::string config_file_name);

      // Copy constructor
      EnvBlackBox(EnvBlackBox& other);

      // Copy constructor
      EnvBlackBox(const EnvBlackBox& other);

      // Destructor
      virtual ~EnvBlackBox();

      // Copy assignment operator
      EnvBlackBox& operator= (EnvBlackBox& other);

      // Copy assignment operator
      EnvBlackBox& operator= (const EnvBlackBox& other);

    protected:
      void copy_blackbox(EnvBlackBox& other);
      void copy_blackbox(const EnvBlackBox& other);

    public:
      void create(std::string result_file_prefix, std::string config_file_name);

    private:
      std::vector<int> find_nearest(BlackBoxState &state, std::vector<BlackBoxState> &other, unsigned int count);
      bool is_in(std::vector<int> &v, int num);

    private:
      void save_image(std::string file_name);

};



#endif
