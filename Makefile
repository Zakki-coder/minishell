NAME = minishell
DIR_SRCS = src
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SRC := $(wildcard src/*.c)
OBJ := $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SRC:%.c=%.o) inc/minishell.h
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

clean:
	rm -f $(OBJ)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all