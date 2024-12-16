/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:29 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 03:48:45 by miwasa           ###   ########.fr       */
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
	// 最初が'-'で、以降すべて'n'で、かつ'n'以外の文字がない場合
	// 例: -n, -nn, -nnn...
	return (j > 1 && arg[j] == '\0');
}

int	builtin_echo(char **argv)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	// argv[i]が-nオプション形式(-n, -nn, -nnn...)である限りループ
	while (argv[i] && is_n_option(argv[i]))
	{
		n_flag = 1;
		i++;
	}
	// オプション解析後、残りの引数を出力
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
