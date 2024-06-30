CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = \
    data_init.c \
    ft_atoi.c \
    philosophers.c \
    philo_utils.c \
	routine.c

OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(NAME)
fclean: clean
	rm -f $(NAME)
re: fclean all
