/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:12:48 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 17:15:17 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\0');
}

static t_token_type	handle_pipe(const char *line, size_t *i)
{
	(void)line;
	(*i)++;
	return (T_PIPE);
}

static t_token_type	handle_in(const char *line, size_t *i)
{
	(*i)++;
	if (line[*i] == '<')
	{
		(*i)++;
		return (T_HEREDOC);
	}
	return (T_REDIR_IN);
}

static t_token_type	handle_out(const char *line, size_t *i)
{
	(*i)++;
	if (line[*i] == '>')
	{
		(*i)++;
		return (T_APPEND);
	}
	return (T_REDIR_OUT);
}

t_token_type	detect_type(const char *line, size_t *i)
{
	if (line[*i] == '|')
		return (handle_pipe(line, i));
	else if (line[*i] == '<')
		return (handle_in(line, i));
	else if (line[*i] == '>')
		return (handle_out(line, i));
	return (T_END);
}
