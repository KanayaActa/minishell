/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:43:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 07:14:39 by miwasa           ###   ########.fr       */
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
	t_command	*cmd;

	while (1)
	{
		cmd = get_parsed_command(shell);
		if (!cmd)
			break ;
		if (handle_heredocs(shell, cmd) < 0)
			continue ;
		if (execute_command_list(shell, cmd) < 0)
			continue ;
	}
}
