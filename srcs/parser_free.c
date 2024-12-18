/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:13:22 by ysugo             #+#    #+#             */
/*   Updated: 2024/12/17 19:15:03 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command_args(t_command *cmd)
{
	int	i;

	if (!cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		xfree(cmd->argv[i]);
		i++;
	}
	xfree(cmd->argv);
}

static void	free_command_redirs(t_redir *redir)
{
	t_redir	*rn;

	while (redir)
	{
		rn = redir->next;
		xfree(redir->filename);
		xfree(redir);
		redir = rn;
	}
}

void	free_command_list(t_command *cmd)
{
	t_command	*n;

	while (cmd)
	{
		n = cmd->next;
		free_command_args(cmd);
		free_command_redirs(cmd->redir);
		xfree(cmd);
		cmd = n;
	}
}
