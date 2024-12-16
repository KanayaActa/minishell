/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 04:08:23 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 04:19:23 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(const char *k)
{
	int	i;

	// must not start with digit and only alnum and '_'
	if (!ft_isalpha(k[0]) && k[0] != '_')
		return (0);
	i = 1;
	while (k[i])
	{
		if (!ft_isalnum(k[i]) && k[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_export(t_minishell *shell, char **argv)
{
	char	*eq;
	char	*key;
	char	*val;
	int		i;
	size_t	klen;
	char	*oldval;
	char	*newval;
	int		append;

	if (!argv[1])
	{
		// print all env in format declare -x ...
		i = 0;
		while (shell->envp[i])
		{
			printf("declare -x %s\n", shell->envp[i]);
			i++;
		}
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		append = 0;
		if (eq)
		{
			// Check if we have +=
			if (eq > argv[i] && eq[-1] == '+')
			{
				// += case
				klen = (eq - 1) - argv[i]; // key length until '+'
				key = ft_substr(argv[i], 0, klen);
				val = ft_strdup(eq + 1);
				append = 1;
			}
			else
			{
				// normal = case
				klen = eq - argv[i];
				key = ft_substr(argv[i], 0, klen);
				val = ft_strdup(eq + 1);
			}
			// validate key
			if (!is_valid_key(key))
			{
				ft_fprintf(stderr,
					"minishell: export: `%s': not a valid identifier\n",
					argv[i]);
				xfree(key);
				xfree(val);
				i++;
				continue ;
			}
			if (append)
			{
				// append mode
				oldval = env_get_value(shell->envp, key);
				if (oldval)
				{
					newval = ft_strjoin(oldval, val);
					env_set_value(&shell->envp, key, newval);
					xfree(newval);
				}
				else
				{
					// key not exist, just set
					env_set_value(&shell->envp, key, val);
				}
			}
			else
			{
				// normal set
				env_set_value(&shell->envp, key, val);
			}
			xfree(key);
			xfree(val);
		}
		else
		{
			// no '=' found, means just setting empty value if key valid
			// e.g. export KEY
			key = ft_strdup(argv[i]);
			if (!is_valid_key(key))
			{
				ft_fprintf(stderr,
					"minishell: export: `%s': not a valid identifier\n",
					argv[i]);
				xfree(key);
				i++;
				continue ;
			}
			// set empty value if not exist
			env_set_value(&shell->envp, key, "");
			xfree(key);
		}
		i++;
	}
	return (0);
}
