CC = cc
NAME = philo

CFLAGS = -Wall -Wextra -Werror
#------------------
SRC = main.c eating.c monitors.c getters.c philosophers.c routine.c
SRC += utils/split.c utils/ft_strcnmp.c utils/substr.c utils/utilss.c utils/tools.c
SRC += time.c tools.c setters.c ft_free.c
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