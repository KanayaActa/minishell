/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_mainutils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:26:41 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 21:56:56 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_no_eq_case(t_minishell *shell, char *arg)
{
	char	*key;

	key = ft_strdup(arg);
	if (!is_valid_key(key))
	{
		export_key_error(arg);
		xfree(key);
		return (1);
	}
	env_set_value(&shell->envp, key, "");
	xfree(key);
	return (0);
}
