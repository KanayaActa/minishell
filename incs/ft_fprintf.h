/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysugo <ysugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:36:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/17 17:37:16 by ysugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include "minishell.h"

int	ffprintf_handle_s(const char **p, va_list args);
int	ffprintf_handle_d(const char **p, va_list args);
int	ffprintf_handle_c(const char **p, va_list args);
int	ffprintf_handle_percent(const char **p);
int	ffprintf_handle_other(const char **p);
int	ft_fprintf(FILE *stream, const char *fmt, ...);

#endif