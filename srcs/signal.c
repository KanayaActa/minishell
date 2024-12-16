/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:09:34 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/16 17:15:04 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_received_signal = 0;

static void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_received_signal = SIGINT;
		// ysugo以下の行をコメントアウトしてもしなくても挙動が変わらない。理由は不明
		// write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
}

int	set_signals(void)
{
	struct sigaction act;
	act.sa_handler = signal_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL))
	{
		perror("minishell: sigaction");
		return SYSTEM_ERR;
	}

	// SIGQUITは無視
	struct sigaction act_ignore;
	act_ignore.sa_handler = SIG_IGN;
	act_ignore.sa_flags = 0;
	sigemptyset(&act_ignore.sa_mask);
	if (sigaction(SIGQUIT, &act_ignore, NULL))
	{
		perror("minishell: sigaction");
		return SYSTEM_ERR;
	}

	return NOERR;
}
