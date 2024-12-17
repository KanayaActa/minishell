/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 04:08:23 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 21:42:04 by ysugo            ###   ########.fr       */
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

void	export_key_error(char *arg)
{
	ft_fprintf(stderr,
		"minishell: export: `%s': not a valid identifier\n", arg);
}

int	builtin_export(t_minishell *shell, char **argv)
{
	int		i;
	char	*eq;
	int		ret;

	if (!argv[1])
	{
		print_export_env_sorted(shell);
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
