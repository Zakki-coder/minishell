NAME = minishell
DIR_SRCS = src
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC := $(wildcard inc/*.h)
SRC := $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)
DEP := $(wildcard libft/*.c)
DEP += $(wildcard libft/GNL/*.c)
DEP += $(wildcard libft/ft_printf/*.c)

all: $(NAME)

$(NAME): $(DEP:%.c=%.o) $(SRC:%.c=%.o) $(INC)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

%.o: %.c
	$(CC) $(CFLAG) -c $(<) -o $(@)

clean:
	rm -f $(OBJ)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all