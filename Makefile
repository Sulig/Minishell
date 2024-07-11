# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadoming <sadoming@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 15:55:31 by sadoming          #+#    #+#              #
#    Updated: 2024/07/10 17:17:54 by sadoming         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
# ------------------ #
# Flags:

CC	:= gcc
FLAGS	:= -lreadline -Llibft -lft
CFLAGS	:= -Wall -Wextra -Werror -g -fsanitize=address
# ------------------ #
# Directories:

LIB_DIR = ./libft
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./include

# Minishell SRC Directories:
SRC_DIR = ./src
BLT_DIR = $(SRC_DIR)/builtins
ENV_DIR = $(SRC_DIR)/env
EXE_DIR = $(SRC_DIR)/exec
PER_DIR = $(SRC_DIR)/print_errors
RED_DIR = $(SRC_DIR)/redirect
SIG_DIR = $(SRC_DIR)/signals
UTL_DIR = $(SRC_DIR)/utils
HER_DIR = $(SRC_DIR)/heredoc

# ------------------- #
# Sources:
MAK = Makefile # This Makefile

LIBFT = $(LIB_DIR)/libft.a # The Libft

# Readline libraries ->
RL_FLAGS = -lreadline -Llibft -lft

# HEADERS
HEADERS = $(INC_DIR)/ $(LIB_DIR)/include/

# DEPENDENCIES ->
INCS	:=	minishell.h
DEPS = $(OBJS:%.o=%d)
-include $(DEPS)

## MINISHELL SRC ->
SRC_SRC = minishell_main.c ft_readline.c manage_structs.c tokenizer.c\
		  check_valid_syntax.c checkfor_unclosedquotes.c split_intocomands.c\
		  split_intodoublelist.c redirect_and_execute.c

BLT_SRC = builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c\
		  builtin_export.c builtin_pwd.c builtin_unset.c cd_utils.c\
		  cd_utils2.c export_utils.c

ENV_SRC = env_get_varname.c env_name_len.c env_set_var.c\
		  find_var_index_from_env.c find_var_line_from_env.c\
		  get_var_from_env.c get_vars_from_env.c\
		  remove_env_var.c

EXE_SRC = exec_utils.c execute_builtin.c execute_comand.c\
		  exec_cmd.c get_executable.c

PER_SRC = print_common_errors.c print_errors.c

RED_SRC = fork_or_die.c link_input_file.c link_output_file.c link_read_end.c\
		  link_write_end.c open_file.c pipe_or_die.c redirect.c\
		  save_restore_stdio.c wait_children.c

SIG_SRC = signals.c signals_utils.c

UTL_SRC = print_utils.c set_path.c filltokens_utils.c is_builtin.c\
		  splitline_intotokens.c expand_heredoc_vars.c\
		  arrof_tokens_utils.c agroup_tokens.c fillcomands_utils.c\
		  quote_removal.c expand_vars.c join_pathwithargs.c\
		  dobefore_execve.c check_comand.c

UTL_SRC += ft_arr_2d.c libft_utils.c libft_utils2.c libft_utils3.c\
			builtin_utils.c ft_strjoin_free.c token_utils.c\
			replace_exit_status.c prepare_echo.c

HER_SRC = read_heredocs.c heredoc_filename.c clear_heredocs.c link_heredoc.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_SRC))
SRC += $(addprefix $(BLT_DIR)/, $(BLT_SRC))
SRC += $(addprefix $(ENV_DIR)/, $(ENV_SRC))
SRC += $(addprefix $(EXE_DIR)/, $(EXE_SRC))
SRC += $(addprefix $(RED_DIR)/, $(RED_SRC))
SRC += $(addprefix $(PER_DIR)/, $(PER_SRC))
SRC += $(addprefix $(SIG_DIR)/, $(SIG_SRC))
SRC += $(addprefix $(UTL_DIR)/, $(UTL_SRC))
SRC += $(addprefix $(HER_DIR)/, $(HER_SRC))

OBJS 	= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
INC	:=	$(addprefix $(INC_DIR)/, $(INCS))

# **************************************************************************** #
#-------------------------------------------------------------#
all: $(LIBFT) $(NAME)
#-------------------------------------------------------------#
author:
	@echo "\033[1;34m\n~ **************************************** ~\n"
	@echo "  ~ \tMade by sadoming && jguillot \t  ~\n"
	@echo "~ **************************************** ~\n\n"
#-------------------------------------------------------------#
#-------------------------------------------------------------#
norm:
	@echo "\n\033[1;93m~ Norminette:\n"
	@norminette -R CheckForbiddenSourceHeader $(LIB_DIR)
	@norminette -R CheckForbiddenSourceHeader $(HEADERS)
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)
	@echo "\n~~~~~~~~~~~~~~~~~~~~~~\n"
	@norminette $(LIB_DIR)
	@norminette $(HEADERS)
	@norminette $(SRC_DIR)
	@echo "\033[1;32m\n ~ Norminette:\t~ OK\n"
	@echo "~~~~~~~~~~~~~~~~~~~~~~\n"
#-------------------------------------------------------------#
#-------------------------------------------------------------#
run: $(NAME)
	@echo "\033[1;34m\n~ **************************************** ~\n"
	@echo " ~ Running ./$(NAME)"
	@echo "\n~ **************************************** ~\033[0;37m\n"
	@./$(NAME)
#-------------------------------------------------------------#
#-------------------------------------------------------------#
# **************************************************************************** #
# LIBFT ->
$(LIBFT):
	@echo "\033[0;33m\n * Compiling Libft -->\033[0;37m\n"
	@make -s -C $(LIB_DIR)
	@echo "\033[1;37m~ **************************************** ~\n"
# ----------------------------------------
# MINISHELL ->
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile libft/libft.a
#mkdir -p $(OBJ_DIR) $(OBJ_DIR)/builtins $(OBJ_DIR)/print_errors $(OBJ_DIR)/utils $(OBJ_DIR)/exec $(OBJ_DIR)/env $(OBJ_DIR)/redirect
	@mkdir -p $(@D)
ifdef CPPFLAGS
	$(CC) -I $(INC_DIR) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
else
	$(CC) -I $(INC_DIR) $(CFLAGS) -c $< -o $@
endif
# ----------------------------------------
$(NAME): $(MAK) $(HEADERS) $(LIBFT) $(OBJS)
	@echo "\033[1;93m\n * Making $(NAME) -->\033[0;37m\n"
	$(CC) $(OBJS) $(FLAGS) $(CFLAGS) -o $@
	@echo "\033[1;32m\n $(NAME) Compiled Successfully\033[0;37m\n"

# **************************************************************************** #
# **************************************************************************** #
# Debugging region:

debug: $(NAME)
	@echo " ~ Debugging ./$(NAME)"
	@lldb $(NAME)

# ------------------

val: $(NAME)
	@echo " ~ Running valgrind ./$(NAME)"
	@valgrind ./$(NAME)

val-strict: $(NAME)
	@echo " ~ Running valgrind ./$(NAME)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
# **************************************************************************** #
# Clean region
clean:
	@make -s clean -C $(LIB_DIR)
	@/bin/rm -frd $(OBJ_DIR)

fclean:	clean
	@make -s fclean -C $(LIB_DIR)
	@/bin/rm -f $(NAME)
	@/bin/rm -frd $(NAME).dSYM
	@echo "\033[1;34m All cleaned succesfully\033[1;97m\n"

clear: fclean
	@find . -name ".DS_Store" -type f -delete
	@clear

re: fclean all

.PHONY:	all author clean clear debug fclean norm re run val val-strict
# **************************************************************************** #
