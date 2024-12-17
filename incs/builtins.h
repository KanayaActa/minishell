/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:55:40 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 22:05:15 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		builtin_echo(char **argv);
int		builtin_cd(t_minishell *shell, char **argv);
int		builtin_pwd(void);
int		builtin_export(t_minishell *shell, char **argv);
int		builtin_unset(t_minishell *shell, char **argv);
int		builtin_env(t_minishell *shell);
int		builtin_exit(t_minishell *shell, char **argv);

int		is_builtin(char *cmd);
int		run_builtin(t_minishell *shell, char **argv);

int		handle_eq_case(t_minishell *shell, char *arg, char *eq);
int		is_valid_key(const char *k);
void	export_key_error(char *arg);
int		handle_no_eq_case(t_minishell *shell, char *arg);
void	print_export_env_sorted(t_minishell *shell);
int		get_key_length(const char *s);
void	free_env_copy(char **env_copy);
void	print_line(const char *entry);

#endif
