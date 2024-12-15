/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:43:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/15 17:26:39 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	// shell_loop(&shell);
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
	for (int i = 0; shell->envp[i]; i++)
		xfree(shell->envp[i]);
	xfree(shell->envp);
}
