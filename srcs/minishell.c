/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:43:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 05:55:17 by miwasa           ###   ########.fr       */
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
	int			old_stdin;
	int			old_stdout;

	while (1)
	{
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
			break ;
		}
		if (*line)
			add_history(line);
		cmd = parse_line(shell, line);
		xfree(line);
		if (!cmd)
			continue ;
		if (cmd->next == NULL && cmd->argv && cmd->argv[0]
			&& is_builtin(cmd->argv[0]))
		{
			old_stdin = dup(0);
			old_stdout = dup(1);
			if (open_redirs(cmd) < 0)
			{
				ft_fprintf(stderr, "redirection error\n");
				dup2(old_stdin, 0);
				dup2(old_stdout, 1);
				close(old_stdin);
				close(old_stdout);
				free_command_list(cmd);
				continue ;
			}
			shell->last_status = run_builtin(shell, cmd->argv);
			dup2(old_stdin, 0);
			dup2(old_stdout, 1);
			close(old_stdin);
			close(old_stdout);
		}
		else
		{
			shell->last_status = execute_pipeline(shell, cmd);
		}
		free_command_list(cmd);
	}
}
