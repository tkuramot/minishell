/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:20:26 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/27 15:55:00 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

static t_token	*init_token(char *word, t_token_type type)
{
	t_token	*token;

	if (!word)
		return (NULL);
	token = ft_calloc(1, sizeof (t_token));
	if (!token)
		return (NULL);
	token->word = word;
	token->type = type;
	return (token);
}

static t_token	*extract_word(char **line)
{
	char	*tmp;
	int64_t	i;
	t_token	*token;

	tmp = *line;
	i = 0;
	while (tmp[i] && is_word(tmp[i]))
		i++;
	token = init_token(ft_substr(tmp, 0, i), TK_WORD);
	*line += i;
	return (token);
}

static t_token	*extract_metacharacter(char **line)
{
	const char	*ops[] = {"|", "<", ">"};
	char		*word;
	size_t		i;
	t_token		*token;

	i = 0;
	word = NULL;
	while (i < sizeof(ops) / sizeof (*ops))
	{
		if (start_with(*line, ops[i]))
		{
			word = ft_strdup(ops[i]);
			break ;
		}
		i++;
	}
	token = init_token(word, TK_OP);
	*line += ft_strlen(ops[i]);
	return (token);
}

t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		if (is_blank(*line))
			consume_blank(&line);
		else if (is_word(*line))
		{
			cur->next = extract_word(&line);
			cur = cur->next;
		}
		else if (is_metacharacter(*line))
		{
			cur->next = extract_metacharacter(&line);
			cur = cur->next;
		}
	}
	return (head.next);
}