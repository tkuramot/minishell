/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:20:26 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/27 13:51:49 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>

t_token	*init_token(char *word, t_token_type type)
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

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool is_metacharacter(char c)
{
	return (c && ft_strchr("|&<> \t\n", c));
}

void	consume_blank(char **line)
{
	if (is_blank(**line))
		(*line)++;
}

bool	start_with(char *s, const char *prefix)
{
	return (ft_strncmp(s, prefix, ft_strlen(prefix)) == 0);
}

bool	is_word(char * s)
{
	return (*s && !is_metacharacter(*s));
}

bool	is_operator(char *s)
{
	const char *ops[] = {"|", "<", ">"};
	size_t	i;

	i = 0;
	while (i < sizeof(ops) / sizeof (*ops))
	{
		if (start_with(s, ops[i]))
			return (true);
		i++;
	}
	return (false);
}

t_token	*extract_word(char **line)
{
	char	*tmp;
	int64_t	i;
	t_token	*token;

	tmp = *line;
	i = 0;
	while (tmp[i] && is_word(&tmp[i]))
		i++;
	token = init_token(ft_substr(tmp, 0, i), TK_WORD);
	*line += i;
	return (token);
}

t_token	*extract_operator(char **line)
{
	const char *ops[] = {"|", "<", ">"};
	char	*word;
	size_t	i;
	t_token	*token;

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

t_token *tokenize(char *line)
{
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		if (is_blank(*line))
			consume_blank(&line);
		else if (is_word(line))
		{
			cur->next = extract_word(&line);
			cur = cur->next;
		}
		else if (is_operator(line))
		{
			cur->next = extract_operator(&line);
			cur = cur->next;
		}
	}
	return (head.next);
}
