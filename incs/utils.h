/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:18:09 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/16 21:05:54 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>

void	*xmalloc(size_t size);
void	*xrealloc(void *ptr, size_t size);
void	xfree(void *ptr);
char	*ft_strjoin_free(char *s1, char *s2);
int ft_fprintf(FILE *stream, const char *fmt, ...);

#endif