/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:23:24 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:43:15 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_new(char **new, int i)
{
	int	j;

	// iはnew[i]が失敗したインデックスなので、それより前の0～i-1を解放する
	j = 0;
	while (j < i)
	{
		free(new[j]);
		j++;
	}
	free(new);
}

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
	char	*newval;
	char	**new;

	klen = ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, klen) && (*envp)[i][klen] == '=')
		{
			newval = xmalloc(klen + ft_strlen(value) + 2);
			ft_strncpy(newval, key, klen);
			newval[klen] = '=';
			ft_strcpy(newval + klen + 1, value);
			free((*envp)[i]);
			(*envp)[i] = newval;
			return (0);
		}
		i++;
	}
	// not found, append
	new = xrealloc(*envp, (i + 2) * sizeof(char *));
	*envp = new;
	newval = xmalloc(klen + ft_strlen(value) + 2);
	ft_strncpy(newval, key, klen);
	newval[klen] = '=';
	ft_strcpy(newval + klen + 1, value);
	(*envp)[i] = newval;
	(*envp)[i + 1] = NULL;
	return (0);
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
