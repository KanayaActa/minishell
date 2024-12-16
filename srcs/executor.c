/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:00:42 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 05:34:55 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void close_fds(int *fds, int count)
// {
//     for(int i = 0; i < count; i++)
//         if(fds[i] >= 0)
//             close(fds[i]);
// }

static void	ignore_signals_for_async(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	open_redirs(t_command *c)
{
	t_redir		*r;
	char		template[sizeof("/tmp/minishell_heredocXXXXXX")];
	char		*delimiter;
	char		*line;
	int			fd;

	strcpy(template, "/tmp/minishell_heredocXXXXXX");
	r = c->redir;
	fd = -1; // Initialize fd to -1
	while (r)
	{
		if (r->type == R_INPUT)
			fd = open(r->filename, O_RDONLY);
		else if (r->type == R_OUTPUT)
			fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == R_APPEND)
			fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (r->type == R_HEREDOC)
		{
			fd = mkstemp(template);
			if (fd < 0)
				return (-1);
			// ここではまだunlinkしないでおく
			delimiter = r->filename;
			line = NULL;
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
			// 書き込み終了後、一旦クローズ
			close(fd);
			// ファイルを読み取りモードで再オープンして先頭から読み込めるようにする
			fd = open(template, O_RDONLY);
			if (fd < 0)
			{
				unlink(template); // 開けなかった場合は削除してエラー
				return (-1);
			}
			// 再オープン後にファイルをunlinkすることで、ファイルはこのプロセスがクローズするまで残るが名前は消える
			unlink(template);
		}
		if (fd < 0)
			return (-1);
		if (r->type == R_INPUT || r->type == R_HEREDOC)
		{
			if (dup2(fd, STDIN_FILENO) < 0)
				return (-1);
			close(fd);
		}
		else
		{
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (-1);
			close(fd);
		}
		r = r->next;
	}
	return (0);
}

static char	*find_cmd_in_path(t_minishell *shell, char *cmd)
{
	char	*path;
	char	**paths;
	char	*f;
	char	*fp;
	int		i;
	int		j;

	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	path = env_get_value(shell->envp, "PATH");
	if (!path)
	{
		path = __builtin_alloca(sizeof("./"));
		strcpy(path, "./");
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		f = ft_strjoin(paths[i], "/");
		fp = ft_strjoin_free(f, ft_strdup(cmd));
		if (access(fp, X_OK) == 0)
		{
			j = 0;
			while (paths[j])
			{
				xfree(paths[j]);
				j++;
			}
			xfree(paths);
			return (fp);
		}
		xfree(fp);
		i++;
	}
	// Free paths
	j = 0;
	while (paths[j])
	{
		xfree(paths[j]);
		j++;
	}
	xfree(paths);
	return (NULL);
}

static void	exec_cmd(t_minishell *shell, t_command *c)
{
	char	*path;

	if (!c->argv || !c->argv[0])
		exit(shell->last_status);
	if (is_builtin(c->argv[0]))
	{
		// Execute built-in in child process
		exit(run_builtin(shell, c->argv));
	}
	path = find_cmd_in_path(shell, c->argv[0]);
	if (!path)
	{
		ft_fprintf(stderr, "minishell: %s: command not found\n", c->argv[0]);
		exit(127);
	}
	execve(path, c->argv, shell->envp);
	ft_fprintf(stderr, "minishell: execve error: %s\n", strerror(errno));
	exit(126);
}

int	execute_pipeline(t_minishell *shell, t_command *cmd)
{
	int			count;
	int			**pipes;
	pid_t		*pids;
	t_command	*c;
	int			status;
	int			sigint_flag;
	int			sigquit_flag;
	int			i;
	int			j;

	// Count commands
	count = 0;
	c = cmd;
	while (c)
	{
		c = c->next;
		count++;
	}
	pipes = NULL;
	if (count > 1)
	{
		pipes = xmalloc(sizeof(int *) * (count - 1));
		i = 0;
		while (i < count - 1)
		{
			pipes[i] = xmalloc(sizeof(int) * 2);
			if (pipe(pipes[i]) < 0)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
	pids = xmalloc(sizeof(pid_t) * count);
	c = cmd;
	i = 0;
	while (i < count)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			// Child process
			// Reset signals to default
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			// Redirect input if not first command
			if (i > 0)
			{
				if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			// Redirect output if not last command
			if (i < count - 1)
			{
				if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			// Close all pipe fds in child
			if (pipes)
			{
				j = 0;
				while (j < count - 1)
				{
					close(pipes[j][0]);
					close(pipes[j][1]);
					j++;
				}
			}
			// Handle redirections
			if (open_redirs(c) < 0)
			{
				ft_fprintf(stderr, "minishell: redirection error\n");
				exit(EXIT_FAILURE);
			}
			// Execute command
			exec_cmd(shell, c);
		}
		c = c->next;
		i++;
	}
	// Parent process closes all pipe fds
	if (pipes)
	{
		i = 0;
		while (i < count - 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			xfree(pipes[i]);
			i++;
		}
		xfree(pipes);
	}
	ignore_signals_for_async(); // 条件分岐で実行
	// Wait for all children
	sigint_flag = 0;
	sigquit_flag = 0;
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			shell->last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT && !sigint_flag)
			{
				// reset_signal_handlers();
				// ignore_signals_for_async(); // 条件分岐で実行
				write(STDERR_FILENO, "\n", 1);
				sigint_flag = 1;
			}
			if (WTERMSIG(status) == SIGQUIT)
			{
				sigquit_flag = 1;
			}
			shell->last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	if (WTERMSIG(status) == SIGQUIT && sigquit_flag)
	{
		ft_fprintf(stderr, "Quit (core dumped)\n");
	}
	xfree(pids);
	return (shell->last_status);
}
