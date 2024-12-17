/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:52:59 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 19:37:58 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// For storing redirections
typedef enum e_redir_type
{
	R_INPUT,
	R_OUTPUT,
	R_APPEND,
	R_HEREDOC
}						t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;
	char				*filename;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**argv;
	t_redir				*redir;
	struct s_command	*next;
}						t_command;

t_command				*parse_line(t_minishell *shell, const char *line);
void					free_command_list(t_command *cmd);

t_redir					*redir_new(t_redir_type type, char *file);
void					redir_add_back(t_redir **lst, t_redir *new);

int	process_token(t_minishell *shell, t_token **p, t_command **cmds, t_command **cur);

#endif