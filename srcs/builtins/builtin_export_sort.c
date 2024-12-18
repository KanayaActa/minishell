/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:56:32 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/18 01:12:17 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	key_compare_core(const char *s1, const char *s2)
{
	int	l1;
	int	l2;
	int	cmp_len;
	int	res;

	l1 = get_key_length(s1);
	l2 = get_key_length(s2);
	if (l1 < l2)
		cmp_len = l1;
	else
		cmp_len = l2;
	res = ft_strncmp(s1, s2, cmp_len);
	if (res == 0)
		res = l1 - l2;
	return (res);
}

static int	compare_env_keys(const void *a, const void *b)
{
	const char	*s1_ptr;
	const char	*s2_ptr;

	s1_ptr = *(const char **)a;
	s2_ptr = *(const char **)b;
	return (key_compare_core(s1_ptr, s2_ptr));
}

static char	**copy_envp_for_sort(char **envp, int count)
{
	char	**copy;
	int		i;

	copy = xmalloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	print_and_free_env_copy(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		print_line(env_copy[i]);
		i++;
	}
	free_env_copy(env_copy);
}

void	print_export_env_sorted(t_minishell *shell)
{
	int		count;
	char	**env_copy;

	count = 0;
	while (shell->envp[count])
		count++;
	env_copy = copy_envp_for_sort(shell->envp, count);
	ft_qsort(env_copy, count, sizeof(char *), compare_env_keys);
	print_and_free_env_copy(env_copy);
}
