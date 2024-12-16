/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:43:28 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:55:20 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H



# define NOERR 0
# define SYSTEM_ERR 1

# include "struct.h"
# include "parser.h"
# include "builtins.h"
# include "env.h"
# include "executor.h"
# include "expands.h"
# include "lexer.h"
# include "libft.h"
# include "signals.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_received_signal;

void							init_shell(t_minishell *shell, char **envp);
void							clean_env_table(t_minishell *shell);
void							shell_loop(t_minishell *shell);

#endif