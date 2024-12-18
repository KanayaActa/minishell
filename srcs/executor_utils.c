/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:45:24 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/18 09:07:22 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ignore_signals_for_async(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_cmd(t_minishell *shell, t_command *c)
{
	char	*path;

	if (!c->argv || !c->argv[0])
		exit(shell->last_status);
	if (is_builtin(c->argv[0]))
		exit(run_builtin(shell, c->argv, 1));
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

int	handle_signals_in_status(int status, int *sigint_flag)
{
	if (WTERMSIG(status) == SIGINT && !(*sigint_flag))
	{
		write(STDERR_FILENO, "\n", 1);
		*sigint_flag = 1;
	}
	return (128 + WTERMSIG(status));
}

void	handle_single_child(t_minishell *shell, pid_t pid,
		int *sigint_flag, int *sigquit_flag)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_status = handle_signals_in_status(status,
				sigint_flag);
	*sigquit_flag = WTERMSIG(status);
}

void	print_sigquit_if_needed(int sigquit_flag)
{
	if (sigquit_flag == SIGQUIT)
		ft_fprintf(stderr, "Quit (core dumped)\n");
}
