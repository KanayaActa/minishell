/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:29:20 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/18 07:14:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

t_command	*get_parsed_command(t_minishell *shell)
{
	char		*line;
	t_command	*cmd;

	line = read_input_line(shell);
	if (!line)
		return (NULL);
	cmd = parse_line(shell, line);
	xfree(line);
	return (cmd);
}

int	handle_heredocs(t_minishell *shell, t_command *cmd)
{
	if (prepare_heredocs(shell, cmd) < 0)
	{
		free_command_list(cmd);
		return (-1);
	}
	return (0);
}

int	execute_command_list(t_minishell *shell, t_command *cmd)
{
	if (cmd->next == NULL && cmd->argv && cmd->argv[0]
		&& is_builtin(cmd->argv[0]))
	{
		if (execute_single_builtin(shell, cmd) < 0)
		{
			free_command_list(cmd);
			return (-1);
		}
	}
	else
	{
		shell->last_status = execute_pipeline(shell, cmd);
	}
	free_command_list(cmd);
	return (0);
}
