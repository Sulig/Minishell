# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguillot <jguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 15:55:31 by sadoming          #+#    #+#              #
#    Updated: 2024/05/27 17:23:20 by jguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
# ------------------ #
# Flags:

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS = $(addprefix -L, $(dir $(LIBFT)))
INCFLAG = -I $(INC_DIR)/ -I $(LIB_DIR)/include/
# ------------------ #
# Directories:

OBJ_DIR = ./obj
LIB_DIR = ./libft
RDL_DIR = ./readline
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
#READLINE = ./readline/libreadline.a
#HISTORY = ./readline/libhistory.a

#READLINE
RL_DIR		= readline/
INCFLAG		+= -I $(RL_DIR)
READLINE	:= $(RL_DIR)libreadline.a $(RL_DIR)libhistory.a
RL_FILE		= readline.tar.gz
RL_URL		= http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-bfe9c573a9e376323929c80b2b71c59727fab0cc.tar.gz

LIBS		= -lreadline -ltermcap
RM			= rm -fr
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
DEFS		= -DREADLINE_LIBRARY
DFLAGS		= -MT $@ -MMD -MP
#XFLAGS		= -fsanitize=address

# HEADERS
HEADERS = $(INC_DIR)/ $(LIB_DIR)/include/

# MINISHELL SRC ->
SRC_SRC = minishell_main.c minishell_welcome.c ft_readline.c tokenizer.c\
		  manage_structs.c check_valid_syntax.c parse_the_tokens.c\
		  checkfor_unclosedquotes.c split_intodoublelist.c\
		  create_cmd_from_cmd.c

SRC_SRC += redirect_and_execute.c

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

UTL_SRC = expand_vars.c fill_token_location.c polish_comands.c print_utils.c\
		  quote_removal.c set_path.c trim_input.c is_builtin.c\
		  fill_comand_options.c ft_strjoin_free.c expand_vars_utils.c\
		  replace_exit_status.c

UTL_SRC += ft_arr_2d.c libft_utils.c libft_utils2.c libft_utils3.c builtin_utils.c

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

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# DEPENDENCIES ->
DEPS = $(OBJS:%.o=%d)
-include $(DEPS)

# **************************************************************************** #
#-------------------------------------------------------------#
all: $(LIBFT) $(READINE) $(NAME)
#-------------------------------------------------------------#
#-------------------------------------------------------------#
$(RL_DIR):
			@curl -k $(RL_URL) > $(RL_FILE)
			@tar -xf $(RL_FILE) && mv readline-* readline
			@rm -rf $(RL_FILE)

#-------------------------------------------------------------#
#-------------------------------------------------------------#
help:
	@echo "\033[1;37m\n ~ Posible comands:\n"
	@echo "\t~ all  \t\t #-> Make $(NAME)\n"
	@echo "\t~ clean \t #-> Clean *.o\n"
	@echo "\t~ fclean \t #-> Clean all\n"
	@echo "\t~ clear \t #-> Clean all & clear\n"
	@echo "\t~ norm \t\t #-> Run norminette\n"
	@echo "\t~ run  \t\t #-> Run $(NAME)\n"
	@echo "\t~ re   \t\t #-> Redo $(NAME)\n"
	@make -s author
#-------------------------------------------------------------#
#-------------------------------------------------------------#
author:
	@echo "\033[1;34m\n~ **************************************** ~\n"
	@echo "  ~ \tMade by sadoming \t  ~\n"
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
# *****************************************************************************
# Compiling Region:

# LIBFT ->
$(LIBFT):
	@echo "\033[0;33m\n * Compiling Libft -->\033[0;37m\n"
	@make -s -C $(LIB_DIR)
	@echo "\033[1;37m~ **************************************** ~\n"
# ----------------------------------------
# READLINE ->
$(READLINE): $(RL_DIR)
			@if [ ! -f $(RL_DIR)config.status ] ; then \
				printf "\t$(YELLOW)Configuring READLINE...$(DEFAULT)" && \
				cd ./$(RL_DIR) && \
				./configure &> /dev/null && \
				echo ✅; \
			fi
			@printf "\t$(YELLOW)Making READLINE...$(DEFAULT)"
			@cd ./$(RL_DIR) && make &> /dev/null
			@echo ✅
# ----------------------------------------
# MINISHELL ->
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT) $(HEADERS)
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(XFLAGS) $(DEFS) $(DFLAGS) $(INCFLAG) -c $< -o $@
			@printf "\t$(YELLOW)$< $(GREEN)compiled$(DEFAULT)\n"

$(NAME): $(MAK) $(HEADERS) $(LIBFT) $(READLINE) $(OBJS)
	@echo "\033[1;93m\n * Making $(NAME) -->\033[0;37m\n"
	@$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) -l ft $(XFLAGS) $(DEFS) $(LIBS) $(READLINE) -o $(NAME)
	@echo "\033[1;32m\n $(NAME) Compiled Successfully\033[0;37m\n"

# **************************************************************************** #
# **************************************************************************** #
# Debugging region:

debug: $(NAME)
	@echo " ~ Debugging ./$(NAME)"
	@lldb $(NAME)

# ------------------

leaks: $(NAME)
	@echo " ~ Running leaks -atExit -- ./$(NAME)"
	@leaks -atExit -- ./$(NAME)

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
	@if [ -d $(RDL_DIR) ]; then \
		make -s clean -C $(RDL_DIR); \
	fi
	@/bin/rm -frd $(OBJ_DIR)
	@echo "\033[1;34m\n All obj removed\033[1;97m\n"


fclean: clean
	@make -s fclean -C $(LIB_DIR)
	@/bin/rm -f $(NAME)
	@/bin/rm -frd $(NAME).dSYM
	@find . -name ".DS_Store" -type f -delete
	@clear
	@echo "\033[1;34m All cleaned succesfully\033[1;97m\n"

clear: fclean
	@clear

re: fclean all
# -------------------- #
.PHONY: all author clean clear debug fclean help leaks norm re run val
# **************************************************************************** #
