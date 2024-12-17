/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:09:15 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 16:42:36 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline(t_minishell *shell, t_command *cmd)
{
	int		count;
	int		**pipes;
	pid_t	*pids;

	count = count_commands(cmd);
	pipes = setup_pipes(count);
	pids = fork_processes(shell, cmd, count, pipes);
	close_all_pipes(count, pipes);
	wait_for_children(shell, count, pids);
	return (shell->last_status);
}
