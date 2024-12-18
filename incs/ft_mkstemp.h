/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mkstemp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:50:20 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 10:57:39 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MKSTEMP_H
# define FT_MKSTEMP_H

void	fill_padded_number(int num, char *buf);
char	*find_placeholder(char *template);
int		create_unique_file(char *template, char *xpos, int num, char *buf);
int		check_num_limit(int num);
int		increment_num_or_fail(int *num_ptr);
int		attempt_file_creation(char *template, char *xpos, char *padded, \
int *num_ptr);

#endif