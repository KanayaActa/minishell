/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 05:06:02 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 07:39:14 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	create_heredoc_tempfile(char *template)
{
	int	fd;

	fd = mkstemp(template);
	if (fd < 0)
	{
		ft_fprintf(stderr, "minishell: heredoc: mkstemp error\n");
		return (-1);
	}
	return (fd);
}

static int	run_heredoc_child_process(t_minishell *shell, int fd,
		const char *delimiter)
{
	char	*line;
	char	*expanded;

	set_heredoc_signals();
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			xfree(line);
			break ;
		}
		expanded = expand_variables(shell, line, IS_HEREDOC);
		xfree(line);
		if (expanded)
		{
			write(fd, expanded, ft_strlen(expanded));
			write(fd, "\n", 1);
			xfree(expanded);
		}
	}
	exit(0);
}

static int	execute_heredoc_in_child(t_minishell *shell, int fd,
		const char *delimiter)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		run_heredoc_child_process(shell, fd, delimiter);
	ignore_signals_for_async();
	waitpid(pid, &status, 0);
	set_signals();
	shell->last_status = WEXITSTATUS(status);
	if (WIFEXITED(status) && shell->last_status == 130)
		return (-1);
	return (0);
}

static int	handle_heredoc(t_minishell *shell, t_redir *r)
{
	char	template[sizeof("/tmp/minishell_heredocXXXXXX")];
	int		fd;

	strcpy(template, "/tmp/minishell_heredocXXXXXX");
	fd = create_heredoc_tempfile(template);
	if (fd < 0)
		return (-1);
	if (execute_heredoc_in_child(shell, fd, r->filename) < 0)
	{
		close(fd);
		unlink(template);
		return (-1);
	}
	close(fd);
	xfree(r->filename);
	r->filename = ft_strdup(template);
	if (!r->filename)
	{
		unlink(template);
		return (-1);
	}
	r->type = R_INPUT;
	return (0);
}

int	prepare_heredocs(t_minishell *shell, t_command *cmds)
{
	t_command	*c;
	t_redir		*r;

	c = cmds;
	while (c)
	{
		r = c->redir;
		while (r)
		{
			if (r->type == R_HEREDOC)
			{
				if (handle_heredoc(shell, r) < 0)
					return (-1);
			}
			r = r->next;
		}
		c = c->next;
	}
	return (0);
}
