/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:36:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 08:10:54 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDS_H
# define EXPANDS_H

# include "minishell.h"

typedef struct s_expand_state {
	int		in_s;
	int		in_d;
	size_t	i;
	char	*res;
}	t_expand_state;

char	*expand_variables(t_minishell *shell, const char *str, int is_heredoc);
char	*handle_dollar(t_minishell *shell, const char *str, size_t *i,
			char *res);
char	*append_char(char *res, const char *str, size_t i);
void	toggle_quote_state(char c, int *in_s, int *in_d);
char	*expand_var(t_minishell *shell, const char *var);

#endif