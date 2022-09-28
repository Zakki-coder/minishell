
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

INCLUDES =	-I ./	\
			-I ./GNL	\
			-I ./libft/ft_printf/includes/ft_printf.h

INC_DEP = libft.h ./libft/ft_printf/includes/ft_printf.h ./GNL/get_next_line.h

CFLAG = -Wall -Wextra -Werror 
GNL = GNL
PRINTF = ft_printf
CC = gcc

SRC :=	$(wildcard *.c)	
SRC +=	$(wildcard $(GNL)/*.c)	
SRC +=	$(wildcard $(PRINTF)/*.c)	

OBJ :=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) #$(INC_DEP)
	gcc -c $(CFLAG) $(SRC) $(INCLUDES) 
	ar rc $(NAME) $(OBJ) 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
