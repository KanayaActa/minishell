/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:43:28 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/16 21:05:47 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_minishell
{
	char	**envp;
	int		last_status;
}	t_minishell;

# define NOERR 0
# define SYSTEM_ERR 1

# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>
#include <stdarg.h>
# include "env.h"
# include "utils.h"
# include "signals.h"
# include "parser.h"
# include "lexer.h"
# include "executor.h"
# include "builtins.h"
# include "expands.h"
# include "libft.h"

extern volatile sig_atomic_t g_received_signal;

void	init_shell(t_minishell *shell, char **envp);
void	clean_env_table(t_minishell *shell);
void	shell_loop(t_minishell *shell);

#endif