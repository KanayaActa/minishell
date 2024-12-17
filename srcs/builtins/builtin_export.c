/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 04:08:23 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 20:23:41 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(const char *k)
{
	int	i;

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

static void	print_export_env(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		printf("declare -x %s\n", shell->envp[i]);
		i++;
	}
}

void	export_key_error(char *arg)
{
	ft_fprintf(stderr,
		"minishell: export: `%s': not a valid identifier\n", arg);
}

static int	handle_no_eq_case(t_minishell *shell, char *arg)
{
	char	*key;

	key = ft_strdup(arg);
	if (!is_valid_key(key))
	{
		export_key_error(arg);
		xfree(key);
		return (1);
	}
	env_set_value(&shell->envp, key, "");
	xfree(key);
	return (0);
}

int	builtin_export(t_minishell *shell, char **argv)
{
	int		i;
	char	*eq;
	int		ret;

	if (!argv[1])
	{
		print_export_env(shell);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
			ret = handle_eq_case(shell, argv[i], eq);
		else
			ret = handle_no_eq_case(shell, argv[i]);
		i++;
	}
	return (0);
}
