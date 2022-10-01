NAME = mshell
SRC_D =	src 
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC := $(wildcard $(SRC_D)/*.c)
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC:%.c=%.o)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

clean:
	rm $(OBJ)
	make clean -C ./libft

fclean: clean
	rm $(NAME)
	make fclean -C ./libft

re: fclean all