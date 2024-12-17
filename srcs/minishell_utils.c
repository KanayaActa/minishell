/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:29:20 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 20:30:28 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input_line(t_minishell *shell)
{
	char	*line;

	set_signals();
	line = readline("minishell> ");
	if (g_received_signal == SIGINT)
	{
		shell->last_status = 130;
		g_received_signal = 0;
	}
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

int	execute_single_builtin(t_minishell *shell, t_command *cmd)
{
	int	old_stdin;
	int	old_stdout;

	old_stdin = dup(0);
	old_stdout = dup(1);
	if (open_redirs(cmd) < 0)
	{
		ft_fprintf(stderr, "redirection error\n");
		dup2(old_stdin, 0);
		dup2(old_stdout, 1);
		close(old_stdin);
		close(old_stdout);
		return (-1);
	}
	shell->last_status = run_builtin(shell, cmd->argv);
	dup2(old_stdin, 0);
	dup2(old_stdout, 1);
	close(old_stdin);
	close(old_stdout);
	return (0);
}
