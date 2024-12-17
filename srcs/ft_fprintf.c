/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:33:21 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 17:34:07 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ffprintf_redirect_stdout(FILE *stream)
{
	int	fd;
	int	saved_stdout;

	fd = fileno(stream);
	saved_stdout = -1;
	if (fd != STDOUT_FILENO)
	{
		saved_stdout = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
	}
	return (saved_stdout);
}

static void	ffprintf_restore_stdout(int saved_stdout)
{
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

static int	ffprintf_process_format(const char **p, va_list args)
{
	(*p)++;
	if (**p == 's')
		return (ffprintf_handle_s(p, args));
	else if (**p == 'd')
		return (ffprintf_handle_d(p, args));
	else if (**p == 'c')
		return (ffprintf_handle_c(p, args));
	else if (**p == '%')
		return (ffprintf_handle_percent(p));
	return (ffprintf_handle_other(p));
}

int	ft_fprintf(FILE *stream, const char *fmt, ...)
{
	va_list		args;
	int			saved_stdout;
	int			written;
	const char	*p;

	va_start(args, fmt);
	saved_stdout = ffprintf_redirect_stdout(stream);
	p = fmt;
	written = 0;
	while (*p)
	{
		if (*p == '%')
			written += ffprintf_process_format(&p, args);
		else
			written += printf("%c", *p++);
	}
	va_end(args);
	ffprintf_restore_stdout(saved_stdout);
	return (written);
}
