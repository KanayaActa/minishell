/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:05:25 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/18 07:59:08 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *res, const char *str, size_t i)
{
	char	*tmp;
	char	*ch;

	ch = ft_strndup(&str[i], 1);
	tmp = ft_strjoin_free(res, ch);
	return (tmp);
}

char	*handle_special_dollar(t_minishell *shell, char *res)
{
	char	*e;
	char	*tmp;

	e = expand_var(shell, "?");
	tmp = ft_strjoin_free(res, e);
	return (tmp);
}

char	*handle_normal_dollar(t_minishell *shell, const char *str, size_t *i,
		char *res)
{
	size_t	start;
	char	*var;
	char	*val;
	char	*tmp;

	start = *i;
	if (!((ft_isalpha(str[*i]) || str[*i] == '_')))
	{
		tmp = ft_strjoin_free(res, ft_strndup("$", 1));
		return (tmp);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_strndup(str + start, (*i) - start);
	val = expand_var(shell, var);
	xfree(var);
	tmp = ft_strjoin_free(res, val);
	return (tmp);
}

char	*handle_dollar(t_minishell *shell, const char *str, size_t *i,
		char *res)
{
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (handle_special_dollar(shell, res));
	}
	return (handle_normal_dollar(shell, str, i, res));
}

void	toggle_quote_state(char c, int *in_s, int *in_d)
{
	if (c == '\'' && !(*in_d))
		*in_s = !(*in_s);
	else if (c == '"' && !(*in_s))
		*in_d = !(*in_d);
}
