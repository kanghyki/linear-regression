# **************************************************
# * TARGET NAME                                    *
# **************************************************
MODEL_NAME := model
TRAINING_NAME := training

# **************************************************
# * SOURCE/INCLUDE                                 *
# **************************************************
INC_PATH := ./inc
SRC_PATH := ./src

UTIL_SRC := util.cpp
UTIL_SRCS:= $(addprefix $(SRC_PATH)/, $(UTIL_SRC))
UTIL_OBJS := $(UTIL_SRCS:.cpp=.o)

TRAINING_SRC := training.cpp
TRAINING_SRCS := $(addprefix $(SRC_PATH)/, $(TRAINING_SRC))
TRAINING_OBJS := $(TRAINING_SRCS:.cpp=.o)

MODEL_SRC := model.cpp
MODEL_SRCS := $(addprefix $(SRC_PATH)/, $(MODEL_SRC))
MODEL_OBJS := $(MODEL_SRCS:.cpp=.o)


# **************************************************
# * VARIABLE                                       *
# **************************************************
CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++11
CPPFLAGS := -I $(INC_PATH)

# **************************************************
# * RULE                                           *
# **************************************************
all: $(TRAINING_NAME) $(MODEL_NAME)
.PHONY: all

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TRAINING_NAME): $(UTIL_OBJS) $(TRAINING_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(MODEL_NAME): $(UTIL_OBJS) $(MODEL_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(UTIL_OBJS) $(TRAINING_OBJS) $(MODEL_OBJS)
.PHONY: clean

fclean: clean
	rm -f $(TRAINING_NAME) $(MODEL_NAME)
.PHONY: fclean

re:
	make fclean
	make all
.PHONY: re
