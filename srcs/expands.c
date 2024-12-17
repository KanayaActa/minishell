/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:00:47 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 17:05:46 by ysugo            ###   ########.fr       */
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

char	*expand_variables(t_minishell *shell, const char *str)
{
	char	*res;
	int		in_s;
	int		in_d;
	size_t	i;

	res = ft_strdup("");
	in_s = 0;
	in_d = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && !in_d) || (str[i] == '"' && !in_s))
		{
			toggle_quote_state(str[i], &in_s, &in_d);
			i++;
		}
		else if (str[i] == '$' && !in_s)
			res = handle_dollar(shell, str, &i, res);
		else
		{
			res = append_char(res, str, i);
			i++;
		}
	}
	return (res);
}
