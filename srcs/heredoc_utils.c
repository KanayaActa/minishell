/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 05:26:49 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 05:27:00 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	heredoc_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_received_signal = SIGINT;
		write(STDERR_FILENO, "\n", 1);
		exit(130);
	}
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa_int;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = heredoc_sigint_handler;
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
		perror("sigaction");
}
