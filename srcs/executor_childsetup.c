/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_childsetup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:38:02 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 16:44:52 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static int	child_dup_in_out(int i, int count, int **pipes)
{
	if (i > 0 && dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		return (-1);
	}
	if (i < count - 1 && dup2(pipes[i][1], STDOUT_FILENO) < 0)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

static void	child_close_pipes(int count, int **pipes)
{
	int	j;

	if (!pipes)
		return ;
	j = 0;
	while (j < count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

static void	child_open_redirs_or_exit(t_command *c)
{
	if (open_redirs(c) < 0)
	{
		ft_fprintf(stderr, "minishell: redirection error\n");
		exit(EXIT_FAILURE);
	}
}

void	child_process_setup(t_command *c, int i, int count, int **pipes)
{
	set_child_signals();
	if (child_dup_in_out(i, count, pipes) < 0)
		exit(EXIT_FAILURE);
	child_close_pipes(count, pipes);
	child_open_redirs_or_exit(c);
}
