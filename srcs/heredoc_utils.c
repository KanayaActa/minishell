/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 05:26:49 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 10:34:09 by miwasa           ###   ########.fr       */
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

static void	fill_padded_number(int num, char *buf)
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
	char	*xpos;
	int		fd;
	int		tries = MAX_TRIES;
	static int	num = 0;

	xpos = ft_strnstr(template, "XXXXXX", ft_strlen(template));
	if (!xpos)
	{
		errno = EINVAL;
		return (-1);
	}
	while (tries--)
	{
		char padded[PAD_WIDTH + 1];
		if (num > MAX_NUM)
		{
			errno = EEXIST;
			return (-1);
		}
		fill_padded_number(num, padded);
		ft_memcpy(xpos, padded, PAD_WIDTH);
		fd = open(template, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
			return (fd);
		if (errno != EEXIST)
			return (-1);
		num++;
	}
	errno = EEXIST;
	return (-1);
}
