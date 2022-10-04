NAME = minishell_test
CC = gcc

EMPTY =
SRC = $(wildcard *.c)
SRC += $(wildcard ../../src/*.c)
SRC += $(wildcard ../Unity/src/*.c)
SRC := $(SRC:main.c=$(EMPTY))
SRC := $(SRC:../../src/=$(EMPTY))
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SRC:%.c=%.o)
	@make -C ../../libft
#	$(CC) -c $(wildcard *.c) ../Unity/src/unity.c ../../libft/libft.a
	@$(CC) -o $(NAME) $(OBJ) ../../libft/libft.a
	./minishell_test