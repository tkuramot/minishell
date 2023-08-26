/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:20:26 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/27 07:42:51 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdbool.h>

t_token	*init_token(char *word, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof (t_token));
	if (!token)
		return (NULL);
	token->word = word;
	token->type = type;
	return (token);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool is_metacharacter(char c)
{
	return (c && ft_strchr("|&<>\t\n", c));
}

bool	consume_blank(char **line)
{
	if (is_blank(**line))
	{
		(*line)++;
		return (true);
	}
	return (false);
}

bool	is_word();

bool	is_operator();

t_token	*extract_word();

t_token	*extract_operator();

t_token *tokenize(char *line)
{
	t_token	head;
	int64_t	i;

	i = 0;
	while (line[i])
	{
	}
	return (head.next);
}
