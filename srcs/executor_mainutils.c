/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_mainutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:24:52 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 16:45:08 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_commands(t_command *cmd)
{
	int			count;
	t_command	*c;

	count = 0;
	c = cmd;
	while (c)
	{
		c = c->next;
		count++;
	}
	return (count);
}

int	**setup_pipes(int count)
{
	int	**pipes;
	int	i;

	if (count <= 1)
		return (NULL);
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
	return (pipes);
}

pid_t	*fork_processes(t_minishell *shell, t_command *cmd,
		int count, int **pipes)
{
	pid_t		*pids;
	t_command	*c_temp;
	int			i;

	pids = xmalloc(sizeof(pid_t) * count);
	c_temp = cmd;
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
			child_process_setup(c_temp, i, count, pipes);
			exec_cmd(shell, c_temp);
		}
		c_temp = c_temp->next;
		i++;
	}
	return (pids);
}

void	close_all_pipes(int count, int **pipes)
{
	int	j;

	if (!pipes)
		return ;
	j = 0;
	while (j < count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		xfree(pipes[j]);
		j++;
	}
	xfree(pipes);
}

void	wait_for_children(t_minishell *shell, int count, pid_t *pids)
{
	int	i;
	int	sigint_flag;
	int	sigquit_flag;

	ignore_signals_for_async();
	sigint_flag = 0;
	sigquit_flag = 0;
	i = 0;
	while (i < count)
	{
		handle_single_child(shell, pids[i], &sigint_flag, &sigquit_flag);
		i++;
	}
	print_sigquit_if_needed(sigquit_flag);
	xfree(pids);
}
