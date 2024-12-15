/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 00:43:28 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/15 18:20:40 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env.h"
# include "utils.h"
# include "signal.h"
# include "parser.h"
# include "lexer.h"
# include "executor.h"
# include "builtins.h"
# include "libft.h"

typedef struct s_minishell
{
	char	**envp;
	int		last_status;
}	t_minishell;

extern volatile sig_atomic_t g_received_signal;

void	init_shell(t_minishell *shell, char **envp);
void	clean_env_table(t_minishell *shell);

#endif