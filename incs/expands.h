/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:36:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 20:37:21 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDS_H
# define EXPANDS_H

# include "minishell.h"

char	*expand_variables(t_minishell *shell, const char *str);
char	*handle_dollar(t_minishell *shell, const char *str, size_t *i,
			char *res);
char	*append_char(char *res, const char *str, size_t i);
void	toggle_quote_state(char c, int *in_s, int *in_d);
char	*expand_var(t_minishell *shell, const char *var);

#endif