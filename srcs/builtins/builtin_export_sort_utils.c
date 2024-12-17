/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:02:32 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 22:04:44 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_key_length(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

void	free_env_copy(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		xfree(env_copy[i]);
		i++;
	}
	xfree(env_copy);
}

void	print_line(const char *entry)
{
	char	*eq;
	char	*key;
	char	*value;
	int		idx;

	eq = ft_strchr(entry, '=');
	if (!eq)
	{
		printf("declare -x %s\n", entry);
		return ;
	}
	idx = (int)(eq - entry);
	key = ft_substr(entry, 0, idx);
	value = ft_strdup(eq + 1);
	printf("declare -x %s=\"%s\"\n", key, value);
	xfree(key);
	xfree(value);
}
