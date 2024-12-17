/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:21 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 20:02:13 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_get_path(t_minishell *shell, char **argv)
{
	char	*path;

	if (!argv[1])
	{
		path = env_get_value(shell->envp, "HOME");
		if (!path)
		{
			ft_fprintf(stderr, "minishell: cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (argv[2])
	{
		ft_fprintf(stderr, "minishell: cd: too many arguments\n");
		return (NULL);
	}
	else
		path = argv[1];
	return (path);
}

int	builtin_cd(t_minishell *shell, char **argv)
{
	char	*path;
	char	cwd[1024];

	path = cd_get_path(shell, argv);
	if (!path)
		return (1);
	if (chdir(path) < 0)
	{
		ft_fprintf(stderr, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	getcwd(cwd, 1024);
	env_set_value(&shell->envp, "PWD", cwd);
	return (0);
}
