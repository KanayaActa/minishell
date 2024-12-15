# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 00:14:20 by miwasa            #+#    #+#              #
#    Updated: 2024/12/15 18:27:31 by miwasa           ###   ########.fr        #
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
	env.c \
	utils.c \
	lexer.c \
	expands.c \
	parser.c \
	signal.c \
	builtins.c \
	builtins/builtins_cd.c \
	builtins/builtins_echo.c \
	builtins/builtins_env.c \
	builtins/builtins_exit.c \
	builtins/builtins_export.c \
	builtins/builtins_pwd.c \
	builtins/builtins_unset.c \

OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

.PHONY: all clean fclean re bonus test

all: $(LIBFT) $(NAME)

bonus: all

$(LIBFT):
	$(MAKE) -C $(FT_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

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
