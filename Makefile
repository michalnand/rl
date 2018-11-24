LIBS_RYSY_PATH=$(HOME)/libs/rysy
LIBS_DQN_PATH=$(HOME)/libs/deep_q_network

export LIBS_RYSY_PATH
export LIBS_DQN_PATH

all:
	cd libs_agent && make -j4
	cd libs_env && make -j4
	cd libs_rl_experiment && make -j4
	cd libs_rl_python && make -j4

clean:
	cd libs_agent && make clean
	cd libs_env && make clean
	cd libs_rl_experiment && make clean
	cd libs_rl_python && make clean
