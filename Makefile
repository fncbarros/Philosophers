NAME = philo
SRC = src/main.c src/utils.c src/thread.c src/time.c src/err.c src/thread_utils.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
OBJ = $(SRC:c=o)

%.o: %.c
	$(CC) $(CFLAGS) -pthread -I inc/ -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

debug: clean
	${CC} -g -fsanitize=thread -pthread ${SRC} -o debug ##temporary
	rm -f ${wildcard *.o} ##temporary

leaks:
	${CC} -g -fsanitize=address -pthread ${SRC} -o debug ##temporary
	rm -f ${wildcard *.o} ##temporary

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME) leaks debug ${wildcard *.dSYM} ##temporary

re: fclean all

.PHONY: all clean fclean re leaks ##temporary