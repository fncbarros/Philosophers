NAME = philo
SRC = src/main.c src/utils.c src/thread.c src/time.c src/err.c src/thread_utils.c src/main_utils.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
OBJ = $(SRC:c=o)

%.o: %.c
	$(CC) $(CFLAGS) -I inc/ -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I /inc $(OBJ) -o $(NAME)

# ------------------ TMP -------------------------
debug: CFLAGS+= -g -fsanitize=thread -DDEBUGMODE=1

debug: NAME=debug

debug: re

leaks: CFLAGS+= -g -fsanitize=address -DDEBUGMODE=1

leaks: NAME=debug

leaks: re
# ------------------ TMP -------------------------

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME) leaks debug ${wildcard *.dSYM}

re: fclean all

.PHONY: all clean fclean re leaks ##temporary