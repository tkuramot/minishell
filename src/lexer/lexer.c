/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:20:26 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/20 00:00:19 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdio.h>

static t_token	*extract_word(char **line)
{
	char	*tmp;
	int64_t	i;
	t_token	*token;

	tmp = *line;
	i = 0;
	while (tmp[i] && is_word(tmp[i]))
	{
		if (tmp[i] == SINGLE_QUOTE)
		{
			while (tmp[++i] && tmp[i] != SINGLE_QUOTE)
				i++;
		}
		else if (tmp[i] == DOUBLE_QUOTE)
		{
			while (tmp[++i] && tmp[i] != DOUBLE_QUOTE)
			{
				i++;
			}
		}
		i++;
	}
	token = token_init(ft_substr(tmp, 0, i), TK_WORD);
	*line += i;
	return (token);
}

static t_token	*extract_metacharacter(char **line)
{
	const char	*ops[] = {"|", "<<", ">>", "<", ">"};
	const int	token_type[] = {TK_PIPE, TK_REDIR_HEREDOC, TK_REDIR_APPEND,
			TK_REDIR_IN, TK_REDIR_OUT};
	char		*word;
	size_t		i;

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
	*line += ft_strlen(ops[i]);
	return (token_init(word, token_type[i]));
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
