/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:44 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:58:46 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_minishell *shell, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		env_remove_key(&shell->envp, argv[i]);
		i++;
	}
	return (0);
}
