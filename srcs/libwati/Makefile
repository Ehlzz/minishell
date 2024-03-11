# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 07:12:45 by bedarenn          #+#    #+#              #
#    Updated: 2024/03/11 13:30:39 by bedarenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################################### NAME #####################################
NAME := libwati.a

################################### COMPILER ###################################
CC := clang

################################# DIRECTORIES ##################################
DIR_OBJS := objs/
DIR_SRCS := srcs/

#################################### FILES #####################################

SRCS = \
	wati_isalpha.c wati_isdigit.c wati_isalnum.c wati_isascii.c wati_isprint.c wati_isupper.c wati_islower.c wati_isspace.c \
	wati_tolower.c wati_toupper.c wati_strupper.c wati_strlower.c \
	wati_sig.c wati_abs.c \
	wati_strlen.c wati_strlen_set.c \
	wati_memset.c wati_bzero.c \
	wati_memcpy.c wati_memmove.c wati_strlcpy.c wati_strlcat.c \
	wati_strchr.c wati_strrchr.c wati_memchr.c \
	wati_strncmp.c wati_memcmp.c wati_strnstr.c \
	wati_atoi.c wati_atoll.c wati_itoa.c wati_atoi_base.c wati_atou_base.c \
	wati_calloc.c \
	wati_strdup.c wati_substr.c \
	wati_strjoin.c wati_strtrim.c wati_split.c wati_join.c \
	wati_free_tab.c \
	wati_strmapi.c wati_striteri.c \
	wati_putchar_fd.c wati_putstr_fd.c wati_putendl_fd.c wati_putnbr_fd.c wati_putstrs_fd.c \
	wati_lstnew.c wati_lstlast.c wati_lstsize.c \
	wati_lstadd_front.c wati_lstadd_back.c \
	wati_lstdelone.c wati_lstclear.c wati_lstclean.c \
	wati_lstiter.c wati_lstmap.c \
	wati_lstjoin.c wati_lstsplit.c \
	btree_create_node.c \
	btree_apply_prefix.c btree_apply_infix.c btree_apply_suffix.c \
	btree_insert_data.c btree_search_item.c \
	btree_level_count.c btree_apply_by_level.c \
	wati_printf.c wati_printf_arg.c wati_printf_utils_nbr.c wati_printf_utils_str.c

OBJS = $(addprefix $(DIR_OBJS), $(SRCS:%.c=%.o))

#################################### FLAGS #####################################
CFLAGS := -Wall -Wextra -Werror
IFLAGS := -I.

#################################### RULES #####################################

all:
debug:

$(NAME): $(OBJS)
	@printf "\n$(GREEN)wati_compile $@$(NC)\n"
	@ar rcs $@ $^

$(DIR_OBJS)%.o: %.c
	@mkdir -p $(@D)
	@printf "$(PURPLE)wati_compile $(notdir $<)$(NC) \r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@printf "$(RED)wati_clean objs$(NC)\n"
	@rm -rf $(DIR_OBJS)

fclean: clean
	@printf "$(RED)wati_clean $(NAME)$(NC)\n"
	@rm -f $(NAME)

re: fclean all

all:	$(NAME)
debug:	CFLAGS += -g
debug:	$(NAME)

.PHONY: all clean fclean debug

#################################### COLORS ####################################
RED = \033[0;31m
GREEN = \033[0;32m
BROWN = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m
