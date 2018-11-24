OUTPUT_NAME = libs_agent



INC+= -I.
INC+= -I../libs_env
INC+= -I../libs_agent
INC+= -I$(LIBS_DQN_PATH)/libs_dqn
INC+= -I$(LIBS_RYSY_PATH)/libs_common
INC+= -I$(LIBS_RYSY_PATH)/libs_nn
INC+= -I$(LIBS_RYSY_PATH)/libs_experiment

SRCS+= $(shell find . -name '*.cpp')

CC = g++
CU = nvcc
LD = g++
OBJCOPY = objcopy
OBJDUMP = objdump
SIZE = size
ARCHIVE = ar

CFLAGS = -O2 -Os -fPIC -s -Wall -Wextra -pedantic -std=c++11 $(INC)

OBJS = $(SRCS:.cpp=.o)

all: $(OBJS)
	$(ARCHIVE) rc $(OUTPUT_NAME).a $(OBJS)
	$(CC) -shared -fPIC -o $(OUTPUT_NAME).so $(OBJS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJS) -f
	rm $(OUTPUT_NAME).* -f
