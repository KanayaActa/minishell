/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:21 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 12:51:10 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_minishell *shell, char **argv)
{
	char	*path;
	char	cwd[1024];

	if (!argv[1])
	{
		path = env_get_value(shell->envp, "HOME");
		if (!path)
		{
			ft_fprintf(stderr, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else if (argv[2])
	{
		ft_fprintf(stderr, "minishell: cd: too many arguments\n");
		return (1);
	}
	else
		path = argv[1];
	if (chdir(path) < 0)
	{
		ft_fprintf(stderr, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	getcwd(cwd, 1024);
	env_set_value(&shell->envp, "PWD", cwd);
	return (0);
}
