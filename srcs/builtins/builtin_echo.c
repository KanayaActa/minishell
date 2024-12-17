/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:29 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 12:52:29 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(const char *arg)
{
	int	j;

	if (arg[0] != '-')
		return (0);
	j = 1;
	while (arg[j] == 'n')
		j++;
	return (j > 1 && arg[j] == '\0');
}

int	builtin_echo(char **argv)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	while (argv[i] && is_n_option(argv[i]))
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
