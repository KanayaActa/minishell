/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:34 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 09:19:26 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_numeric_arg(char *arg, int last_status)
{
	long	val;
	char	*endptr;

	if (!arg)
		return (last_status);
	errno = 0;
	val = ft_strtol(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
	{
		ft_fprintf(stderr, "exit\n");
		ft_fprintf(stderr, "minishell: exit: \
%s: numeric argument required\n", arg);
		exit(2);
	}
	return ((int)val);
}

static int	handle_exit_extra_args(char **argv, int is_pipe)
{
	if (argv[2])
	{
		if (!is_pipe)
			ft_fprintf(stderr, "exit\n");
		ft_fprintf(stderr, "minishell: exit: too many arguments\n");
		return (-1);
	}
	return (0);
}

int	builtin_exit(t_minishell *shell, char **argv, int is_pipe)
{
	int	status;

	status = handle_exit_numeric_arg(argv[1], shell->last_status);
	if (handle_exit_extra_args(argv, is_pipe) < 0)
		return (1);
	if (!is_pipe)
		ft_fprintf(stdout, "exit\n");
	exit(status);
}
