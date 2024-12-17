/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:34 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 20:04:14 by ysugo            ###   ########.fr       */
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

static void	handle_exit_extra_args(char **argv)
{
	if (argv[2])
	{
		ft_fprintf(stderr, "exit\n");
		ft_fprintf(stderr, "minishell: exit: too many arguments\n");
		exit(1);
	}
}

int	builtin_exit(t_minishell *shell, char **argv)
{
	int	status;

	status = handle_exit_numeric_arg(argv[1], shell->last_status);
	handle_exit_extra_args(argv);
	ft_fprintf(stdout, "exit\n");
	exit(status);
	return (0);
}
