/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:18:09 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 01:37:41 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>

void	*xmalloc(size_t size);
void	*xrealloc(void *ptr, size_t size);
void	xfree(void *ptr);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_fprintf(FILE *stream, const char *fmt, ...);

#endif