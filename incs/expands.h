/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:36:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:48:55 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDS_H
# define EXPANDS_H

# include "minishell.h"

char	*expand_variables(t_minishell *shell, const char *str);

#endif