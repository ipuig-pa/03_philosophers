NAME = philo

CFLAGS = -Wall -Wextra -Werror

SOURCES = philo.c

OBJECTS = $(SOURCES:.c=.o)

HEADER = philo.h

all: NAME

$(NAME):
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


