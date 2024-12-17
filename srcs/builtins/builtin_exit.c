/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:34 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 12:51:54 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_minishell *shell, char **argv)
{
	long	val;
	char	*endptr;
	int		status;

	if (argv[1])
	{
		errno = 0;
		val = ft_strtol(argv[1], &endptr, 10);
		if (errno != 0 || *endptr != '\0')
		{
			ft_fprintf(stderr, "exit\n");
			ft_fprintf(stderr, "minishell: exit:\
				%s: numeric argument required\n", argv[1]);
			exit(2);
		}
		status = (int)val;
	}
	else
	{
		status = shell->last_status;
	}
	if (argv[2])
	{
		ft_fprintf(stderr, "exit\n");
		ft_fprintf(stderr, "minishell: exit: too many arguments\n");
		exit(1);
	}
	ft_fprintf(stdout, "exit\n");
	exit(status);
	return (0);
}
