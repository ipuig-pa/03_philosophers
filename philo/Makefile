NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

SOURCES =	philo.c \
			manage_env.c \
			threads_and_mutex.c \
			monitor.c \
			routine.c \
			time.c \
			meals.c

OBJECTS = $(SOURCES:.c=.o)

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re