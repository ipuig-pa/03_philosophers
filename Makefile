NAME = philo

CFLAGS = -Wall -Wextra -Werror

SOURCES =	philo.c \
			threads_and_mutex.c \
			routine.c \
			helper.c

OBJECTS = $(SOURCES:.c=.o)

HEADER = philo.h

all: NAME

$(NAME):
	cc $(CFLAGS) -pthread $(OBJECTS) -o $(NAME)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


