
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
INC_DEP = libft.h ft_printf/includes/ft_printf.h gnl/get_next_line.h
GNL = GNL
PRINTF = ft_printf
CFLAG = -Wall -Wextra -Werror
CC = gcc
SRC :=	ft_atoi.c	\
		ft_bzero.c	\
		ft_cpynstrarr.c	\
		ft_equstrlen.c	\
		ft_freeda.c	\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_itoa.c	\
		ft_lstadd.c	\
		ft_lstdel.c	\
		ft_lstdelany.c	\
		ft_lstdelone.c	\
		ft_lstiter.c	\
		ft_lstmap.c	\
		ft_lstnew.c	\
		ft_memalloc.c	\
		ft_memccpy.c	\
		ft_memchr.c	\
		ft_memcmp.c	\
		ft_memcpy.c	\
		ft_memdel.c	\
		ft_memmove.c	\
		ft_memset.c	\
		ft_putchar.c	\
		ft_putchar_fd.c	\
		ft_putendl.c	\
		ft_putendl_fd.c	\
		ft_putnbr.c	\
		ft_putnbr_fd.c	\
		ft_putstr.c	\
		ft_putstr_fd.c	\
		ft_realloc.c	\
		ft_realloc_darray.c	\
		ft_strcat.c	\
		ft_strchr.c	\
		ft_strclr.c	\
		ft_strcmp.c	\
		ft_strcpy.c	\
		ft_strdel.c	\
		ft_strdup.c	\
		ft_strequ.c	\
		ft_striter.c	\
		ft_striteri.c	\
		ft_strjoin.c	\
		ft_strlcat.c	\
		ft_strlen.c	\
		ft_strmap.c	\
		ft_strmapi.c	\
		ft_strncat.c	\
		ft_strncmp.c	\
		ft_strncpy.c	\
		ft_strndup.c	\
		ft_strnequ.c	\
		ft_strnew.c	\
		ft_strnstr.c	\
		ft_strrchr.c	\
		ft_strsplit.c	\
		ft_strstr.c	\
		ft_strsub.c	\
		ft_strtrim.c	\
		ft_tolower.c	\
		ft_toupper.c
SRC +=	gnl/get_next_line.c
SRC +=	ft_printf/float_part_1.c	\
		ft_printf/float_part_2.c	\
		ft_printf/float_part_3.c	\
		ft_printf/ft_printf.c	\
		ft_printf/get_argument_utilities.c	\
		ft_printf/get_format_utilities.c	\
		ft_printf/hexa.c	\
		ft_printf/hexa_part_2.c	\
		ft_printf/integer.c	\
		ft_printf/integer_part_2.c	\
		ft_printf/octal.c	\
		ft_printf/octal_part_2.c	\
		ft_printf/parser_part_1.c	\
		ft_printf/parser_part_2.c	\
		ft_printf/percent.c	\
		ft_printf/put_pointer_address.c	\
		ft_printf/put_string.c	\
		ft_printf/shared_utilities.c
OBJ = $(SRC:%.c=%.o)

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
