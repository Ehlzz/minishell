# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 13:50:42 by ehalliez          #+#    #+#              #
#    Updated: 2023/12/17 20:39:43 by ehalliez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

MY-SOURCES = ft_realloc.c ft_print_stack.c ft_count_strtab.c ft_print_ctab.c get_next_line_bonus.c get_next_line_utils_bonus.c ft_printf.c ft_print_adress.c ft_check_param.c ft_putnbr_base.c ft_split.c ft_atoi.c ft_striteri.c ft_strmapi.c ft_substr.c ft_strtrim.c ft_itoa.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strjoin.c ft_memchr.c ft_memcmp.c ft_isalpha.c ft_strncmp.c ft_strnstr.c ft_strchr.c ft_strrchr.c ft_strdup.c ft_strlcpy.c ft_strlcat.c ft_strlen.c ft_isprint.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_calloc.c ft_toupper.c ft_tolower.c
				
MY-OBJECTS = $(MY-SOURCES:.c=.o)

MY-BONUS = ft_lstmap.c ft_lstiter.c ft_lstclear.c ft_lstdelone.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_lstadd_front.c ft_lstnew.c

MY-BONUSOBJ = $(MY-BONUS:.c=.o)

NAME = libft.a

CFLAGS = -Werror -Wall -Wextra

CC = clang

all: $(NAME)

$(NAME): $(MY-OBJECTS)
	ar rcs $(NAME) $(MY-OBJECTS) 

clean: 
	rm -f $(MY-OBJECTS) $(MY-BONUSOBJ)

fclean: clean
	rm -f libft.a

re: fclean $(NAME)

bonus: $(MY-OBJECTS) $(MY-BONUSOBJ)
	ar rcs $(NAME) $(MY-OBJECTS) $(MY-BONUSOBJ)
	
.PHONY: all clean fclean re bonus
