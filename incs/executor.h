/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:55:46 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:55:47 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

// The executor runs the pipeline of t_command
// Use pipes, fork, execve.
// handle builtins and redirections.
int	execute_pipeline(t_minishell *shell, t_command *cmd);
int	open_redirs(t_command *c);

#endif
