/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:20:45 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 16:45:20 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redirect_fd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
		return (-1);
	close(oldfd);
	return (0);
}

static int	do_redir(t_redir *r)
{
	int		fd;
	char	template[sizeof("/tmp/minishell_heredocXXXXXX")];

	strcpy(template, "/tmp/minishell_heredocXXXXXX");
	fd = -1;
	if (r->type == R_INPUT)
		fd = open(r->filename, O_RDONLY);
	else if (r->type == R_OUTPUT)
		fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == R_APPEND)
		fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (r->type == R_HEREDOC)
		fd = handle_heredoc(template, r);
	return (fd);
}

int	open_redirs(t_command *c)
{
	t_redir	*r;
	int		fd;

	r = c->redir;
	while (r)
	{
		fd = do_redir(r);
		if (fd < 0)
			return (-1);
		if ((r->type == R_INPUT || r->type == R_HEREDOC)
			&& redirect_fd(fd, STDIN_FILENO) < 0)
			return (-1);
		else if ((r->type == R_OUTPUT || r->type == R_APPEND)
			&& redirect_fd(fd, STDOUT_FILENO) < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
