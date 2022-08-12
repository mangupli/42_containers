# Names ---------------------------------------------------

NAME		=   containers_tests
VECTOR		=	vector
STACK		=	stack
MAP			=	map
SUFFIX		=	_tests.cpp

# Containers files-----------------------------------------

CONTAINERS_DIR = ./containers/
CONTAINERS_FILES  = vector.hpp iterator.hpp random_access_iterator.hpp utils.hpp stack.hpp map.hpp tree.hpp
CONTAINERS = $(addprefix $(CONTAINERS_DIR), $(CONTAINERS_FILES))

# Compilation ---------------------------------------------

COMPILER = g++
FLAGS = -std=c++98 -Wall -Wextra -Werror -Wconversion
SCRIPT_DIFF = bash script_diff.sh

# Сolors for beauty ---------------------------------------

YELLOW		=	\033[33;1m
RESET		=	\033[0m
RED			=	\033[31;1m
GREEN		=	\033[32;1m
MAGENTA 	=	\033[35;1m
MY_YELLOW   =	\033[38;5;200m
MY_MAGENTA	=	\033[38;5;200m
DARK_GRAY	=	\033[38;5;245m

ERASE = \33[2K

# Output ?-------------------------------------------------

FCLEAN		=	@echo "$(DARK_GRAY)Executable and tests output removed$(RESET)"
CLEAN		=	@echo "$(MY_YELLOW)Object files removed$(RESET)"
DONE		=	@echo "\$(MY_MAGENTA)Compiled! Executable name: $(NAME)$(RESET)"

# Object files --------------------------------------------

OBJS_DIR = ./tests/objs/
OBJS_FILES = $(SRCS_FILES:.cpp=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_FILES))

# Diffs files ---------------------------------------------

DIFFS_DIR = ./tests/diffs/

# Source files --------------------------------------------

SRCS_FILES = main.cpp \
				stack_tests.cpp vector_tests.cpp map_tests.cpp
SRCS_DIR = ./tests/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))


# Header files --------------------------------------------
HEADERS_FILES = vector_tests.hpp \
				stack_tests.hpp \
					map_tests.hpp \
					tests.hpp \
						Foo.class.hpp
HEADERS_DIR = ./tests/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_FILES))

				
# Rules ---------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS) 
	$(COMPILER) $(OBJS) -o $@
	$(DONE)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp $(HEADERS) $(CONTAINERS)
	@mkdir -p $(OBJS_DIR)
	$(COMPILER) $(FLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	$(CLEAN)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(HEADERS_DIR)/tests_output
	$(FCLEAN)

re: fclean all

.PHONY: all re clean fclean