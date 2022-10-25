
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jniemine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 16:50:01 by jniemine          #+#    #+#              #
#    Updated: 2021/12/22 17:09:44 by jniemine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC_DEP = libft.h ft_printf/includes/ft_printf.h GNL/get_next_line.h

GNL = GNL
PRINTF = ft_printf
CFLAG = -Wall -Wextra -Werror
CC = gcc

SRC :=	$(wildcard *.c)
SRC += $(wildcard $(GNL)/*.c)
SRC += $(wildcard $(PRINTF)/*.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC:%.c=%.o) $(INC_DEP)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAG) -c $(<) -o $(@)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
