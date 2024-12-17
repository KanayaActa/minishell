/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:43:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 20:30:39 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_received_signal;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	set_signals();
	shell_loop(&shell);
	clean_env_table(&shell);
	return (shell.last_status);
}

void	init_shell(t_minishell *shell, char **envp)
{
	shell->envp = env_copy(envp);
	shell->last_status = 0;
}

void	clean_env_table(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		xfree(shell->envp[i]);
		i++;
	}
	xfree(shell->envp);
}

void	shell_loop(t_minishell *shell)
{
	char		*line;
	t_command	*cmd;

	while (1)
	{
		line = read_input_line(shell);
		if (!line)
			break ;
		cmd = parse_line(shell, line);
		xfree(line);
		if (!cmd)
			continue ;
		if (cmd->next == NULL && cmd->argv && cmd->argv[0]
			&& is_builtin(cmd->argv[0]))
		{
			if (execute_single_builtin(shell, cmd) < 0)
			{
				free_command_list(cmd);
				continue ;
			}
		}
		else
			shell->last_status = execute_pipeline(shell, cmd);
		free_command_list(cmd);
	}
}
