# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcoqueir <gcoqueir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 10:33:46 by bedos-sa          #+#    #+#              #
#    Updated: 2023/11/01 14:00:40 by gcoqueir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c srcs
vpath %.c bonus

NAME = minishell

CC = cc
FLAGS = -lreadline $(LIBFT)/libft.a
CFLAGS = -Wall -Wextra -Werror -I$(LIBS) -O3 -g3

LIBFT = ./libft
LIBS = ./include
OBJ_DIR = build/
INIT_DIR = init_utils/
FIX_INPUT_DIR = fix_input/
BUILT_DIR = builtin/
SIG_DIR = signal/
TOKEN_DIR = token/
EXEC_DIR = exec/
REDIRECT_DIR = redirect/
FREE_DIR = free/

RM = rm -f
FILES = main.c \
		$(INIT_DIR)init_utils.c \
		$(BUILT_DIR)execute_builtin.c \
		$(BUILT_DIR)exit.c \
		$(BUILT_DIR)env.c \
		$(BUILT_DIR)pwd.c \
		$(BUILT_DIR)unset.c \
		$(BUILT_DIR)export.c \
		$(BUILT_DIR)export_utils.c \
		$(BUILT_DIR)export_split_key_and_value.c \
		$(BUILT_DIR)echo.c \
		$(BUILT_DIR)cd.c \
		$(SIG_DIR)signal.c \
		$(TOKEN_DIR)token.c \
		$(TOKEN_DIR)lexer.c \
		$(TOKEN_DIR)syntax.c \
		$(FIX_INPUT_DIR)fix_input.c \
		$(FIX_INPUT_DIR)expansion.c \
		$(FIX_INPUT_DIR)expand_utils.c \
		$(FIX_INPUT_DIR)check_quotes.c \
		$(FIX_INPUT_DIR)check_tildes.c \
		$(FIX_INPUT_DIR)check_exit_status.c \
		$(EXEC_DIR)exec.c \
		$(EXEC_DIR)child_process.c \
		$(EXEC_DIR)finally_execute.c \
		$(EXEC_DIR)child_dups.c \
		$(EXEC_DIR)pipes.c \
		$(EXEC_DIR)get_cmd_and_builtin.c \
		$(EXEC_DIR)wait_all_process.c \
		$(EXEC_DIR)verify.c \
		$(REDIRECT_DIR)files.c \
		$(REDIRECT_DIR)deal_with_fd.c \
		$(REDIRECT_DIR)here_doc.c \
		$(FREE_DIR)frees.c
		
OBJS = $(FILES:.c=.o)

all: mkdir_obj $(NAME)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

mkdir_obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(INIT_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILT_DIR)
	@mkdir -p $(OBJ_DIR)$(SIG_DIR)
	@mkdir -p $(OBJ_DIR)$(TOKEN_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(REDIRECT_DIR)
	@mkdir -p $(OBJ_DIR)$(FIX_INPUT_DIR)
	@mkdir -p $(OBJ_DIR)$(FREE_DIR)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJS))
	@make -C $(LIBFT) --silent
	@$(CC) $(addprefix $(OBJ_DIR), $(OBJS)) $(FLAGS) -o $(NAME)
	@echo "\033[0;32mSUCCESS!\033[0m"

run: all
	./$(NAME)

val: all
	valgrind --suppressions=./local.supp --quiet --leak-check=full --show-leak-kinds=all ./$(NAME)

bonus: all

clean:
	@make clean -C $(LIBFT) --silent
	@$(RM) $(addprefix $(OBJ_DIR), $(OBJS))
	@echo "\033[0;36mBUILD DIRECTORY CLEAN!\033[0m"

fclean: clean
	@make fclean -C $(LIBFT) --silent
	@$(RM) $(NAME)
	@echo "\033[0;31mBINARY DESTROYED!\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus run val
