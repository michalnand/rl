%module pyrl

%include <std_vector.i>
%include <std_string.i>

%template(VectorChar) std::vector<char>;
%template(VectorUnsignedChar) std::vector<unsigned char>;
%template(VectorInt) std::vector<int>;
%template(VectorUnsignedInt) std::vector<unsigned int>;
%template(VectorFloat) std::vector<float>;
%template(VectorDouble) std::vector<double>;

%template(MatrixInt) std::vector<std::vector<int>>;
%template(MatrixUnsignedInt) std::vector<std::vector<unsigned int>>;

%template(MatrixFloat) std::vector<std::vector<float>>;
%template(MatrixDouble) std::vector<std::vector<double>>;


%apply const std::string& {std::string* foo};



%{
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>

#include <dataset_interface.h>
#include <dataset_cifar.h>
#include <dataset_cifar_10.h>
#include <dataset_images.h>
#include <dataset_landsat.h>
#include <dataset_mnist.h>
#include <dataset_mnist_tiny.h>
#include <dataset_pair.h>
#include <dataset_preprocessing.h>
#include <dataset_tic_tac_toe.h>

#include <dqn.h>
#include <ddqn.h>
#include <dqn_compare.h>
#include <dqnp.h>
#include <random_distribution.h>


#include <agent_hyperparameters.h>
#include <state.h>
#include <agent.h>
#include <agent_ddqn.h>
#include <agent_dqn.h>
#include <agent_dqnp.h>
#include <agent_q_table.h>
#include <agent_sarsa_table.h>

#include <env.h>
#include <blackbox_state.h>
#include <perlin_noise.h>
#include <env_blackbox.h>
#include <env_catcher.h>
#include <env_cliff.h>
#include <env_frozen_lake.h>
#include <env_pong.h>
#include <arcade/env_arcade.h>
#include <ball_balance/env_ball_balance.h>
#include <pacman/env_pacman.h>
#include <snake/env_snake.h>
#include <stack/env_stack.h>

#include <visualisation/glvisualisation.h>


#include <rl_log.h>
#include <rl_summary_result.h>
#include <rl_experiment.h>



%}


%include <dataset_interface.h>
%include <dataset_cifar.h>
%include <dataset_cifar_10.h>
%include <dataset_images.h>
%include <dataset_landsat.h>
%include <dataset_mnist.h>
%include <dataset_mnist_tiny.h>
%include <dataset_pair.h>
%include <dataset_preprocessing.h>
%include <dataset_tic_tac_toe.h>

%include <dqn.h>
%include <ddqn.h>
%include <dqn_compare.h>
%include <dqnp.h>
%include <random_distribution.h>


%include <agent_hyperparameters.h>
%include <state.h>
%include <agent.h>
%include <agent_ddqn.h>
%include <agent_dqn.h>
%include <agent_dqnp.h>
%include <agent_q_table.h>
%include <agent_sarsa_table.h>

%include <env.h>
%include <blackbox_state.h>
%include <perlin_noise.h>
%include <env_blackbox.h>
%include <env_catcher.h>
%include <env_cliff.h>
%include <env_frozen_lake.h>
%include <env_pong.h>
%include <arcade/env_arcade.h>
%include <ball_balance/env_ball_balance.h>
%include <pacman/env_pacman.h>
%include <snake/env_snake.h>
%include <stack/env_stack.h>

%include <visualisation/glvisualisation.h>


%include <rl_log.h>
%include <rl_summary_result.h>
%include <rl_experiment.h>
