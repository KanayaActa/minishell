/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:23:24 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/15 17:25:40 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	**env_copy(char **envp)
{
	int		count;
	char	**new;

	count = 0;
	while(envp[count])
		count++;
	new=malloc((count + 1) * sizeof(char*));
	if (!new)
		exit(1); // ここの終了ステータスexitでいい？
	for (int i=0;i<count;i++)
		new[i]=ft_strdup(envp[i]); //NULLガードいれる
	new[count]=NULL;
	return (new);
}
