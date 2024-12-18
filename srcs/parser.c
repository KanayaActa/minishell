/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:07:45 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 19:54:59 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_new(t_redir_type type, char *file)
{
	t_redir	*r;

	r = xmalloc(sizeof(t_redir));
	r->type = type;
	r->filename = file;
	r->next = NULL;
	return (r);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*p;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
}

t_command	*cmd_new(void)
{
	t_command	*c;

	c = xmalloc(sizeof(t_command));
	c->argv = NULL;
	c->redir = NULL;
	c->next = NULL;
	return (c);
}

void	add_arg(t_command *cmd, char *arg)
{
	int	count;

	count = 0;
	if (cmd->argv)
		while (cmd->argv[count])
			count++;
	cmd->argv = xrealloc(cmd->argv, (count + 2) * sizeof(char *));
	cmd->argv[count] = arg;
	cmd->argv[count + 1] = NULL;
}

t_redir_type	token_to_redir(t_token_type t)
{
	if (t == T_REDIR_IN)
		return (R_INPUT);
	if (t == T_REDIR_OUT)
		return (R_OUTPUT);
	if (t == T_APPEND)
		return (R_APPEND);
	if (t == T_HEREDOC)
		return (R_HEREDOC);
	return (R_INPUT);
}
