/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:23:24 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 16:55:57 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_copy(char **envp)
{
	int		count;
	char	**new;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new = xmalloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count)
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
		{
			cleanup_new(new, i);
			exit(1);
		}
		i++;
	}
	new[count] = NULL;
	return (new);
}

char	*env_get_value(char **envp, const char *key)
{
	size_t	klen;
	int		i;

	klen = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, klen) && envp[i][klen] == '=')
			return (envp[i] + klen + 1);
		i++;
	}
	return (NULL);
}

int	env_set_value(char ***envp, const char *key, const char *value)
{
	size_t	klen;
	int		i;

	klen = ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, klen) && (*envp)[i][klen] == '=')
			return (env_update_value(envp, i, key, value));
		i++;
	}
	return (env_add_value(envp, i, key, value));
}

void	env_remove_key(char ***envp, const char *key)
{
	size_t	klen;
	int		i;
	int		j;

	klen = ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, klen) && (*envp)[i][klen] == '=')
		{
			free((*envp)[i]);
			j = i;
			while ((*envp)[j])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

void	env_print(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
