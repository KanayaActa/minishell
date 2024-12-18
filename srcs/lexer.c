/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:00:51 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/18 00:21:24 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*token_new(t_token_type type, char *val)
{
	t_token	*t;

	t = xmalloc(sizeof(t_token));
	t->type = type;
	t->value = val;
	t->next = NULL;
	return (t);
}

static void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*p;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
}

static char	*read_word(const char *line, size_t *i)
{
	size_t	start;
	int		in_squote;
	int		in_dquote;

	start = *i;
	in_squote = 0;
	in_dquote = 0;
	while (line[*i])
	{
		if (!in_squote && !in_dquote && is_metachar(line[*i]))
			break ;
		if (!in_squote && line[*i] == '"' && !in_dquote)
			in_dquote = 1;
		else if (in_dquote && line[*i] == '"')
			in_dquote = 0;
		else if (!in_dquote && line[*i] == '\'' && !in_squote)
			in_squote = 1;
		else if (in_squote && line[*i] == '\'')
			in_squote = 0;
		else if (!in_squote && !in_dquote && (line[*i] == ' '
				|| line[*i] == '\t'))
			break ;
		(*i)++;
	}
	return (ft_substr(line, start, *i - start));
}

t_token	*lexer_tokenize(const char *line)
{
	t_token			*tokens;
	size_t			i;
	t_token_type	tt;
	char			*w;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			tt = detect_type(line, &i);
			token_add_back(&tokens, token_new(tt, ft_strdup("")));
		}
		else
		{
			w = read_word(line, &i);
			token_add_back(&tokens, token_new(T_WORD, w));
		}
	}
	return (tokens);
}

void	free_token_list(t_token *tokens)
{
	t_token	*n;

	while (tokens)
	{
		n = tokens->next;
		xfree(tokens->value);
		xfree(tokens);
		tokens = n;
	}
}
