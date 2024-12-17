/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_processtoken.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:17:37 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 19:17:59 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipe_token(t_command **cmds, t_command **cur, t_token **p)
{
	t_command	*newc;

	newc = cmd_new();
	newc->next = *cmds;
	*cmds = newc;
	*cur = newc;
	*p = (*p)->next;
}

static int	handle_word_token(t_minishell *shell, t_command *cur, t_token **p)
{
	char	*expanded;

	expanded = expand_variables(shell, (*p)->value);
	add_arg(cur, expanded);
	*p = (*p)->next;
	return (0);
}

static int	handle_redir_token(t_minishell *shell, t_command *cur, t_token **p)
{
	char			*expanded;
	t_redir_type	rt;

	rt = token_to_redir((*p)->type);
	*p = (*p)->next;
	if (!*p || (*p)->type != T_WORD)
		return (-1);
	expanded = expand_variables(shell, (*p)->value);
	redir_add_back(&cur->redir, redir_new(rt, expanded));
	*p = (*p)->next;
	return (0);
}

int	process_token(t_minishell *shell, t_token **p,
		t_command **cmds, t_command **cur)
{
	if (!*cur)
	{
		*cur = cmd_new();
		(*cur)->next = *cmds;
		*cmds = *cur;
	}
	if ((*p)->type == T_PIPE)
		handle_pipe_token(cmds, cur, p);
	else if ((*p)->type == T_WORD)
	{
		if (handle_word_token(shell, *cur, p) < 0)
			return (-1);
	}
	else if ((*p)->type == T_REDIR_IN || (*p)->type == T_REDIR_OUT
		|| (*p)->type == T_APPEND || (*p)->type == T_HEREDOC)
	{
		if (handle_redir_token(shell, *cur, p) < 0)
			return (-1);
	}
	return (0);
}
