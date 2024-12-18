/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mkstemp_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:48:04 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 10:55:52 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_placeholder(char *template)
{
	char	*xpos;

	xpos = ft_strnstr(template, "XXXXXX", ft_strlen(template));
	if (!xpos)
	{
		errno = EINVAL;
		return (NULL);
	}
	return (xpos);
}

int	create_unique_file(char *template, char *xpos, int num, char *buf)
{
	int	fd;

	fill_padded_number(num, buf);
	ft_memcpy(xpos, buf, PAD_WIDTH);
	fd = open(template, O_CREAT | O_EXCL | O_RDWR, 0600);
	if (fd >= 0)
		return (fd);
	return (-1);
}

int	check_num_limit(int num)
{
	if (num > MAX_NUM)
	{
		errno = EEXIST;
		return (-1);
	}
	return (0);
}

int	increment_num_or_fail(int *num_ptr)
{
	if (errno == EEXIST)
	{
		(*num_ptr)++;
		return (0);
	}
	return (-1);
}

int	attempt_file_creation(char *template, char *xpos, char *padded,
		int *num_ptr)
{
	int	fd;
	int	tries;

	tries = MAX_TRIES;
	while (tries--)
	{
		if (check_num_limit(*num_ptr) < 0)
			return (-1);
		fd = create_unique_file(template, xpos, *num_ptr, padded);
		if (fd >= 0)
			return (fd);
		if (increment_num_or_fail(num_ptr) < 0)
			return (-1);
	}
	errno = EEXIST;
	return (-1);
}
