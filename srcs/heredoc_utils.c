/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 05:26:49 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 10:56:52 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	heredoc_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_received_signal = SIGINT;
		write(STDERR_FILENO, "\n", 1);
		exit(130);
	}
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa_int;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = heredoc_sigint_handler;
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
		perror("sigaction");
}

void	fill_padded_number(int num, char *buf)
{
	char	*num_str;
	size_t	len;

	num_str = ft_itoa(num);
	len = ft_strlen(num_str);
	ft_memset(buf, '0', PAD_WIDTH);
	buf[PAD_WIDTH] = '\0';
	if (len < PAD_WIDTH)
		ft_memcpy(buf + (PAD_WIDTH - len), num_str, len);
	else
		ft_memcpy(buf, num_str, PAD_WIDTH);
	free(num_str);
}

int	ft_mkstemp(char *template)
{
	char		*xpos;
	char		padded[PAD_WIDTH + 1];
	static int	num = 0;

	xpos = find_placeholder(template);
	if (!xpos)
		return (-1);
	ft_memset(padded, 0, sizeof(padded));
	return (attempt_file_creation(template, xpos, padded, &num));
}
