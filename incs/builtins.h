/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:55:40 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 12:52:40 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	builtin_echo(char **argv);
int	builtin_cd(t_minishell *shell, char **argv);
int	builtin_pwd(void);
int	builtin_export(t_minishell *shell, char **argv);
int	builtin_unset(t_minishell *shell, char **argv);
int	builtin_env(t_minishell *shell);
int	builtin_exit(t_minishell *shell, char **argv);

int	is_builtin(char *cmd);
int	run_builtin(t_minishell *shell, char **argv);

#endif
