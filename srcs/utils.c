/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:44:39 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 10:18:55 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
	{
		fprintf(stderr, "minishell: allocation error\n");
		exit(1);
	}
	return (p);
}

static size_t	xrealloc_count_old(char **old)
{
	size_t	old_count;

	old_count = 0;
	while (old[old_count])
		old_count++;
	return (old_count);
}

void	*xrealloc(void *ptr, size_t size)
{
	char	**old;
	size_t	old_count;
	void	*newp;
	size_t	new_count;
	size_t	copy_count;

	if (!ptr)
		return (xmalloc(size));
	if (size == 0)
	{
		xfree(ptr);
		return (NULL);
	}
	old = (char **)ptr;
	old_count = xrealloc_count_old(old);
	newp = xmalloc(size);
	new_count = size / sizeof(char *);
	if (old_count + 1 < new_count)
		copy_count = old_count + 1;
	else
		copy_count = new_count;
	ft_memcpy(newp, old, copy_count * sizeof(char *));
	xfree(old);
	return (newp);
}

void	xfree(void *ptr)
{
	if (ptr)
		free(ptr);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	xfree(s1);
	xfree(s2);
	return (res);
}
