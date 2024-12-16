/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:23:24 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:14:50 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_copy(char **envp)
{
	int		count;
	char	**new;

	count = 0;
	while (envp[count])
		count++;
	new = malloc((count + 1) * sizeof(char *));
	if (!new)
		exit(1); // ここの終了ステータスexitでいい？
	for (int i = 0; i < count; i++)
		new[i] = ft_strdup(envp[i]); // NULLガードいれる
	new[count] = NULL;
	return (new);
}

char	*env_get_value(char **envp, const char *key)
{
	size_t	klen;

	klen = ft_strlen(key);
	for (int i = 0; envp[i]; i++)
	{
		if (!ft_strncmp(envp[i], key, klen) && envp[i][klen] == '=')
			return (envp[i] + klen + 1);
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
	for (i = 0; (*envp)[i]; i++)
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

	klen = ft_strlen(key);
	int i, j;
	for (i = 0; (*envp)[i]; i++)
	{
		if (!ft_strncmp((*envp)[i], key, klen) && (*envp)[i][klen] == '=')
		{
			free((*envp)[i]);
			for (j = i; (*envp)[j]; j++)
				(*envp)[j] = (*envp)[j + 1];
			return ;
		}
	}
}

void	env_print(char **envp)
{
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
}
