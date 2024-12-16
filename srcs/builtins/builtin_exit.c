/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 02:58:34 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 04:20:08 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_minishell *shell, char **argv)
{
	long	val;
	char	*endptr;
	int		status;

	(void)shell;
	if (argv[1])
	{
		errno = 0;
		val = ft_strtol(argv[1], &endptr, 10);
		// strtolの結果がエラーか、あるいはendptrが'\0'でなければ数値以外の文字が残っている
		if (errno != 0 || *endptr != '\0')
		{
			// bashと同様のエラーメッセージを出力
			// minishell: exit: a: numeric argument required
			ft_fprintf(stderr, "exit\n");
			ft_fprintf(stderr, "minishell: exit:\
				%s: numeric argument required\n", argv[1]);
			exit(2);
		}
		status = (int)val; // longをintにキャスト（範囲外の場合は動作未定義ですがここは簡易実装）
	}
	else
	{
		status = 0; // 引数がなければ0で終了
	}
	// 引数が正常に数値なら"exit"を表示する必要があればここで表示
	ft_fprintf(stdout, "exit\n"); // 必要なら有効にする
	exit(status);
	return (0); // ここには到達しない
}
