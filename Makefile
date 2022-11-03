NAME = minishell
DIR_SRCS = src/
DIR_INCS = inc/
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC =	$(DIR_INCS)builtins.h	\
		$(DIR_INCS)env.h	\
		$(DIR_INCS)minishell.h
SRC =	$(DIR_SRCS)builtin_dispatcher.c	\
		$(DIR_SRCS)builtins.c	\
		$(DIR_SRCS)builtins2.c	\
		$(DIR_SRCS)chop_line_to_args.c	\
		$(DIR_SRCS)error_handling.c	\
		$(DIR_SRCS)execute.c	\
		$(DIR_SRCS)executor.c	\
		$(DIR_SRCS)exit.c	\
		$(DIR_SRCS)expander.c	\
		$(DIR_SRCS)get_input.c	\
		$(DIR_SRCS)is_functions.c	\
		$(DIR_SRCS)loop.c	\
		$(DIR_SRCS)main.c	\
		$(DIR_SRCS)ms_cd.c	\
		$(DIR_SRCS)ms_env.c	\
		$(DIR_SRCS)ms_env2.c	\
		$(DIR_SRCS)ms_setenv.c	\
		$(DIR_SRCS)parse_enivorment_variables.c	\
		$(DIR_SRCS)parse_variable.c	\
		$(DIR_SRCS)search_bin.c	\
		$(DIR_SRCS)search_variable.c	\
		$(DIR_SRCS)tilde.c	\
		$(DIR_SRCS)universal.c	\
		$(DIR_SRCS)unsetenv.c
OBJ = $(SRC:%.c=%.o)
DEP := $(wildcard libft/*.c)
DEP += $(wildcard libft/GNL/*.c)
DEP += $(wildcard libft/ft_printf/*.c)

all: $(NAME)

$(NAME): $(DEP:%.c=%.o) $(SRC:%.c=%.o) $(INC)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $(<) -o $(@)

clean:
	rm -f $(OBJ)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all