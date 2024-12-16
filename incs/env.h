/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:28:12 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/16 17:32:34 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "minishell.h"

char	**env_copy(char **envp);
char    *env_get_value(char **envp, const char *key);
int     env_set_value(char ***envp, const char *key, const char *value);
void    env_remove_key(char ***envp, const char *key);
void    env_print(char **envp);

#endif