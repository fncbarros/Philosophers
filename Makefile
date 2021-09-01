NAME = philo
SRC = src/main.c src/utils.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:c=o)

%.o: %.c
	$(CC) $(CFLAGS) -pthread -I inc/ -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re