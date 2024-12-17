/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:09:24 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 19:22:42 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*build_cmd_list(t_minishell *shell, t_token *toks)
{
	t_command	*cmds;

	cmds = NULL;
	if (parse_tokens(shell, toks, &cmds) < 0)
	{
		free_command_list(cmds);
		return (NULL);
	}
	return (cmds);
}

static int	parse_tokens(t_minishell *shell, t_token *p, t_command **cmds)
{
	t_command	*cur;

	cur = NULL;
	while (p)
	{
		if (process_token(shell, &p, cmds, &cur) < 0)
			return (-1);
	}
	reverse_command_list(cmds);
	return (0);
}

static void	reverse_command_list(t_command **cmds)
{
	t_command	*prev;
	t_command	*cur;
	t_command	*nex;

	prev = NULL;
	cur = *cmds;
	while (cur)
	{
		nex = cur->next;
		cur->next = prev;
		prev = cur;
		cur = nex;
	}
	*cmds = prev;
}

t_command	*parse_line(t_minishell *shell, const char *line)
{
	t_token		*toks;
	t_command	*cmds;

	toks = lexer_tokenize(line);
	if (!toks)
		return (NULL);
	cmds = build_cmd_list(shell, toks);
	free_token_list(toks);
	return (cmds);
}

