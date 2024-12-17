/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:15:39 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 16:44:59 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	read_heredoc_lines(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			xfree(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		xfree(line);
	}
	return (0);
}

static int	open_and_finalize_heredoc(char *template)
{
	int	fd;

	close(STDOUT_FILENO);
	fd = open(template, O_RDONLY);
	if (fd < 0)
	{
		unlink(template);
		return (-1);
	}
	unlink(template);
	return (fd);
}

int	handle_heredoc(char *template, t_redir *r)
{
	int	fd;

	signal(SIGQUIT, SIG_IGN);
	fd = mkstemp(template);
	if (fd < 0)
		return (-1);
	if (read_heredoc_lines(fd, r->filename) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (open_and_finalize_heredoc(template));
}
