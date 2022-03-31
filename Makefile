# Names ---------------------------------------------------

NAME		=   containers_tests
VECTOR		=	vector
STACK		=	stack
MAP			=	map
SUFFIX		=	_tests.cpp

# Compilation ---------------------------------------------

COMPILER = c++
FLAGS = -std=c++98 # -Wall -Wextra -Werror -Wconversion
SCRIPT_DIFF = bash script_diff.sh

# Сolors for beauty ---------------------------------------

YELLOW		=	\033[33;1m
RESET		=	\033[0m
RED			=	\033[31;1m
GREEN		=	\033[32;1m
MAGENTA 	=	\033[35;1m

ERASE = \33[2K

# Output ?-------------------------------------------------

FCLEAN		=	@echo "\033[38;5;245mExecutable removed$(RESET)"
CLEAN		=	@echo "\033[38;5;229mObject files removed$(RESET)"
DONE		=	@echo "\033[38;5;200mCompiled! Executable name: $(NAME)$(RESET)"

# Object files --------------------------------------------

OBJS_DIR = ./tests/objs/
OBJS_FILES = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_FILES))

# Diffs files ---------------------------------------------

DIFFS_DIR = ./tests/diffs/
OBJS_FILES = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_FILES))

# Source files #

SRCS_FILES = main.cpp

HEADERS = vector.hpp \
			iterator.hpp \
			iterator_traits.hpp \
			random_access_iterator.hpp \
			utils.hpp \
			reverse_iterator.hpp

# Rules #

all: $(NAME)

$(NAME): $(OBJS)
	$(COMPILER) $(OBJS) -o $@
	$(DONE)

$(OBJS_DIR)%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	$(CLEAN)

fclean: clean
	rm -rf $(NAME)
	$(FCLEAN)

re: fclean all

.PHONY: all re clean fclean