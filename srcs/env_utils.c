/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:01:11 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 16:57:44 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_new(char **new, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(new[j]);
		j++;
	}
	free(new);
}

int	env_update_value(char ***envp, int i,
		const char *key, const char *value)
{
	size_t	klen;
	char	*newval;

	klen = ft_strlen(key);
	newval = xmalloc(klen + ft_strlen(value) + 2);
	ft_strncpy(newval, key, klen);
	newval[klen] = '=';
	ft_strcpy(newval + klen + 1, value);
	free((*envp)[i]);
	(*envp)[i] = newval;
	return (0);
}

int	env_add_value(char ***envp, int i,
		const char *key, const char *value)
{
	size_t	klen;
	char	*newval;
	char	**new;

	klen = ft_strlen(key);
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
