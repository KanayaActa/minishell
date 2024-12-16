/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:34 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:58:37 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_minishell *shell, char **argv)
{
	int	status;

	(void)shell;
	// just exit
	// if has numeric arg use it
	status = 0;
	if (argv[1])
		status = atoi(argv[1]);
	// print message only if needed
	// The subject not specify we must print something
	exit(status);
	return (0); // never reach
}
