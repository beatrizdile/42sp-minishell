# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 10:33:46 by bedos-sa          #+#    #+#              #
#    Updated: 2023/09/11 14:15:47 by bedos-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c srcs
vpath %.c bonus

NAME = minishell

CC = cc
FLAGS = -O3 -g3 -lreadline
CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft
LIBS = /include

RM = rm -f
FILES = main.c \
		frees.c \
		builtin/exit.c
OBJ_DIR = build
BUILT_DIR = builtin

OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I.$(LIBS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(OBJS) $(CFLAGS) $(LIBFT)/libft.a $(FLAGS) -o $(NAME)

val: 
	valgrind --suppressions=./local.supp --leak-check=full ./minishell

bonus: all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(BUILT_DIR)

clean:
	@make clean -C $(LIBFT)
	@$(RM) $(OBJS)
	@rmdir $(OBJ_DIR)/$(BUILT_DIR)
	@rmdir $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
