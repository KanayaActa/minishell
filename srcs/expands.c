/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:00:47 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 08:11:21 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_minishell *shell, const char *var)
{
	char	*val;

	if (!ft_strcmp(var, "?"))
		return (ft_itoa(shell->last_status));
	val = env_get_value(shell->envp, var);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

static int	is_quote_char(char c, int in_s, int in_d)
{
	return ((c == '\'' && !in_d) || (c == '"' && !in_s));
}

static void	process_quote_char(const char *str, int is_heredoc, \
t_expand_state *st)
{
	if (is_heredoc)
	{
		st->res = append_char(st->res, str, st->i);
		st->i++;
	}
	else
	{
		toggle_quote_state(str[st->i], &st->in_s, &st->in_d);
		st->i++;
	}
}

char	*expand_variables(t_minishell *shell, const char *str, int is_heredoc)
{
	t_expand_state	st;

	st.res = ft_strdup("");
	st.in_s = 0;
	st.in_d = 0;
	st.i = 0;
	while (str[st.i])
	{
		if (is_quote_char(str[st.i], st.in_s, st.in_d))
		{
			process_quote_char(str, is_heredoc, &st);
		}
		else if (str[st.i] == '$' && (!st.in_s || is_heredoc))
		{
			st.res = handle_dollar(shell, str, &st.i, st.res);
		}
		else
		{
			st.res = append_char(st.res, str, st.i);
			st.i++;
		}
	}
	return (st.res);
}
