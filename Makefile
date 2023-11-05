# **************************************************
# * TARGET NAME                                    *
# **************************************************
NAME := train

# **************************************************
# * SOURCE/INCLUDE                                 *
# **************************************************
INC_PATH := ./inc
SRC_PATH := ./src
SRC := main.cpp
SRCS := $(addprefix $(SRC_PATH)/, $(SRC))
OBJS := $(SRCS:.cpp=.o)


# **************************************************
# * VARIABLE                                       *
# **************************************************
CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++11
CPPFLAGS := -I $(INC_PATH)

# **************************************************
# * RULE                                           *
# **************************************************
all: $(NAME)
.PHONY: all

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)
.PHONY: clean

fclean: clean
	rm -f $(NAME)
.PHONY: fclean

re:
	make fclean
	make all
.PHONY: re
