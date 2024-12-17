/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:34:10 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 17:39:22 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ffprintf_handle_s(const char **p, va_list args)
{
	char	*s;
	int		written;

	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	written = printf("%s", s);
	(*p)++;
	return (written);
}

int	ffprintf_handle_d(const char **p, va_list args)
{
	int	d;
	int	written;

	d = va_arg(args, int);
	written = printf("%d", d);
	(*p)++;
	return (written);
}

int	ffprintf_handle_c(const char **p, va_list args)
{
	int	c;
	int	written;

	c = va_arg(args, int);
	written = printf("%c", (char)c);
	(*p)++;
	return (written);
}

int	ffprintf_handle_percent(const char **p)
{
	int	written;

	written = printf("%%");
	(*p)++;
	return (written);
}

int	ffprintf_handle_other(const char **p)
{
	int	written;

	written = printf("%%");
	if (**p)
		written += printf("%c", *(*p)++);
	return (written);
}
