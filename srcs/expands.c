/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:00:47 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 03:00:48 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var(t_minishell *shell, const char *var)
{
	char	*val;

	if (!ft_strcmp(var, "?"))
	{
		return (ft_itoa(shell->last_status));
	}
	val = env_get_value(shell->envp, var);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*expand_variables(t_minishell *shell, const char *str)
{
	char	*res;
	int		in_s;
	int		in_d;
	size_t	i;
	char	*e;
	char	*tmp;
	size_t	start;
	char	*var;
	char	*val;

	// handle quotes and expansions
	// 'no expansions in single quotes'
	// expand $VAR and $?
	// skip expansions in single quotes, do in double quotes
	// minimal implementation
	res = ft_strdup("");
	in_s = 0;
	in_d = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_d)
		{
			in_s = !in_s;
			i++;
			continue ;
		}
		if (str[i] == '"' && !in_s)
		{
			in_d = !in_d;
			i++;
			continue ;
		}
		if (str[i] == '$' && !in_s)
		{
			i++;
			if (str[i] == '?')
			{
				i++;
				e = expand_var(shell, "?");
				tmp = ft_strjoin_free(res, e);
				res = tmp;
				continue ;
			}
			// parse var name
			start = i;
			if (!((ft_isalpha(str[i]) || str[i] == '_')))
			{
				// no valid var name, just append '$'
				tmp = ft_strjoin_free(res, ft_strndup("$", 1));
				res = tmp;
				continue ;
			}
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var = ft_strndup(str + start, i - start);
			val = expand_var(shell, var);
			xfree(var);
			tmp = ft_strjoin_free(res, val);
			res = tmp;
		}
		else
		{
			tmp = ft_strjoin_free(res, ft_strndup(&str[i], 1));
			res = tmp;
			i++;
		}
	}
	return (res);
}
