/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:18:04 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/18 09:44:40 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_paths(char **paths)
{
	int	j;

	j = 0;
	while (paths[j])
	{
		xfree(paths[j]);
		j++;
	}
	xfree(paths);
}

static char	*search_path_in_dirs(char **paths, char *cmd)
{
	int		i;
	char	*f;
	char	*fp;

	i = 0;
	while (paths[i])
	{
		f = ft_strjoin(paths[i], "/");
		fp = ft_strjoin_free(f, ft_strdup(cmd));
		if (access(fp, X_OK) == 0)
		{
			free_paths(paths);
			return (fp);
		}
		xfree(fp);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

char	*find_cmd_in_path(t_minishell *shell, char *cmd)
{
	char	*path;
	char	**paths;
	char	buf[3];

	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	path = env_get_value(shell->envp, "PATH");
	if (!path)
	{
		ft_strcpy(buf, "./");
		path = buf;
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (search_path_in_dirs(paths, cmd));
}
