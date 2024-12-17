# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 00:14:20 by miwasa            #+#    #+#              #
#    Updated: 2024/12/17 20:31:35 by ysugo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

FT_DIR		:= ./libft
LIBFT		:= $(FT_DIR)/libft.a
INCS_DIR	:= ./incs
SRCS_DIR	:= ./srcs
OBJS_DIR	:= ./objs

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -I$(INCS_DIR) -I$(FT_DIR)
RLFLAGS		:= -lreadline


SRCS		:= \
	minishell.c \
	minishell_utils.c \
	env.c \
	env_utils.c \
	utils.c \
	ft_fprintf.c \
	ft_fprintf_utils.c \
	lexer.c \
	lexer_utils.c \
	expands.c \
	expands_utils.c \
	parser.c \
	parser_free.c \
	parser_line.c \
	parser_processtoken.c \
	signal.c \
	executor.c \
	executor_childsetup.c \
	executor_heredoc.c \
	executor_mainutils.c \
	executor_path.c \
	executor_redir.c \
	executor_utils.c \
	builtins.c \
	builtins/builtin_cd.c \
	builtins/builtin_echo.c \
	builtins/builtin_env.c \
	builtins/builtin_exit.c \
	builtins/builtin_export.c \
	builtins/builtin_export_utils.c \
	builtins/builtin_pwd.c \
	builtins/builtin_unset.c \

OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

.PHONY: all clean fclean re bonus test

all: $(LIBFT) $(NAME)

bonus: all

$(LIBFT):
	$(MAKE) -C $(FT_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(RLFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	$(MAKE) clean -C $(FT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(FT_DIR)

re: fclean all
