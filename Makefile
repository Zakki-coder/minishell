NAME = mshell
DIR_SRCS = src 
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SRC := $(wildcard src/*.c)
OBJ := $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SRC:%.c=%.o)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

clean:
	echo $(OBJ)
	rm $(OBJ)
	make clean -C ./libft

fclean: clean
	rm $(NAME)
	make fclean -C ./libft

re: fclean all