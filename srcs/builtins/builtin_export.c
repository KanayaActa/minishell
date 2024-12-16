/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:38 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:58:40 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(const char *k)
{
	int	i;

	// must not start with digit and only alnum and _
	if (!ft_isalpha(k[0]) && k[0] != '_')
		return (0);
	i = 1;
	while (k[i] && k[i] != '=')
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
	size_t	klen;
	char	*key;
	char	*val;
	int		i;

	if (!argv[1])
	{
		// print env in format declare -x ...
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
		if (eq)
		{
			klen = eq - argv[i];
			key = ft_substr(argv[i], 0, klen);
			val = ft_strdup(eq + 1);
			if (!is_valid_key(key))
			{
				ft_fprintf(stderr,
					"minishell: export: `%s': not a valid identifier\n",
					argv[i]);
				xfree(key);
				xfree(val);
				continue ;
			}
			env_set_value(&shell->envp, key, val);
			xfree(key);
			xfree(val);
		}
		else
		{
			// just add empty if key not exist
			if (is_valid_key(argv[i]))
				env_set_value(&shell->envp, argv[i], "");
			else
				ft_fprintf(stderr,
					"minishell: export: `%s': not a valid identifier\n",
					argv[i]);
		}
		i++;
	}
	return (0);
}
