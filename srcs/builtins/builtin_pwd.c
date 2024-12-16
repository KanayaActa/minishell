/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:41 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 02:58:43 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, 1024))
	{
		ft_fprintf(stderr, "minishell: pwd: error\n");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
