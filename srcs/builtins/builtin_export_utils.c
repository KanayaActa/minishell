/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:20:33 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 20:24:49 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_append(t_minishell *shell, const char *key, const char *val)
{
	char	*oldval;
	char	*newval;

	oldval = env_get_value(shell->envp, key);
	if (oldval)
	{
		newval = ft_strjoin(oldval, val);
		env_set_value(&shell->envp, key, newval);
		xfree(newval);
	}
	else
		env_set_value(&shell->envp, key, val);
	return (0);
}

static int	handle_invalid_key(char *key, char *val, char *arg)
{
	export_key_error(arg);
	xfree(key);
	xfree(val);
	return (1);
}

static int	handle_append_eq_case(t_minishell *shell, char *arg, char *eq)
{
	size_t	klen;
	char	*key;
	char	*val;

	klen = (eq - 1) - arg;
	key = ft_substr(arg, 0, klen);
	val = ft_strdup(eq + 1);
	if (!is_valid_key(key))
		return (handle_invalid_key(key, val, arg));
	handle_append(shell, key, val);
	xfree(key);
	xfree(val);
	return (0);
}

static int	handle_normal_eq_case(t_minishell *shell, char *arg, char *eq)
{
	size_t	klen;
	char	*key;
	char	*val;

	klen = eq - arg;
	key = ft_substr(arg, 0, klen);
	val = ft_strdup(eq + 1);
	if (!is_valid_key(key))
		return (handle_invalid_key(key, val, arg));
	env_set_value(&shell->envp, key, val);
	xfree(key);
	xfree(val);
	return (0);
}

int	handle_eq_case(t_minishell *shell, char *arg, char *eq)
{
	if (eq > arg && eq[-1] == '+')
		return (handle_append_eq_case(shell, arg, eq));
	else
		return (handle_normal_eq_case(shell, arg, eq));
}
