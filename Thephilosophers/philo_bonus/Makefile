CC = cc
NAME = philo_bonus

# CFLAGS = -Wall -Wextra -Werror
#------------------
SRC = main_bonus.c eating_bonus.c monitor_bonus.c getters_bonus.c  process_bonus.c
SRC += utils_bonus/split.c utils_bonus/ft_strcnmp.c utils_bonus/substr.c utils_bonus/utilss.c utils_bonus/tools.c utils_bonus/ft_itoa.c
SRC += time_bonus.c tools_bonus.c setters_bonus.c
#------------------

OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)