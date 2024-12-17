/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:55:46 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 16:54:23 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
#include <sys/types.h>


void	ignore_signals_for_async(void);
int		handle_heredoc(char *template, t_redir *r);
int		open_redirs(t_command *c);
char	*find_cmd_in_path(t_minishell *shell, char *cmd);
void	exec_cmd(t_minishell *shell, t_command *c);
int		count_commands(t_command *cmd);
int		**setup_pipes(int count);
void	close_all_pipes(int count, int **pipes);
void	child_process_setup(t_command *c, int i, int count, int **pipes);
pid_t	*fork_processes(t_minishell *shell, t_command *cmd, int count, int **pipes);
int		handle_signals_in_status(int status, int *sigint_flag, int *sigquit_flag);
void	handle_single_child(t_minishell *shell, pid_t pid, int *sigint_flag, int *sigquit_flag);
void	print_sigquit_if_needed(int sigquit_flag);
void	wait_for_children(t_minishell *shell, int count, pid_t *pids);
int		execute_pipeline(t_minishell *shell, t_command *cmd);

#endif
