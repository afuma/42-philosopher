
CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g

INCLUDES = -I./include
SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = philo/philosopher.c \
			philo/thread_1.c \
			philo/thread_2.c \
			philo/death.c \
			philo/death_eating.c \
			philo/eating.c \
			philo/free_mutex.c \
			utils/parsing.c \
			utils/error.c \
			utils/utils.c \
			utils/utils_parsing.c \
			utils/free.c \
			init/init.c \
			init/init_mutex.c \
			init/init_philosopher.c

DIRS = $(sort $(dir $(OBJ)))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
DEPS = $(OBJ:.o=.d)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(DIRS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(DEPS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re

-include $(DEPS)