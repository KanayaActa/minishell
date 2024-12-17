/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:28:12 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 20:35:42 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

void	cleanup_new(char **new, int i);
char	**env_copy(char **envp);
char	*env_get_value(char **envp, const char *key);
int		env_update_value(char ***envp, int i,
			const char *key, const char *value);
int		env_add_value(char ***envp, int i, const char *key, const char *value);
int		env_set_value(char ***envp, const char *key, const char *value);
void	env_remove_key(char ***envp, const char *key);
void	env_print(char **envp);

#endif