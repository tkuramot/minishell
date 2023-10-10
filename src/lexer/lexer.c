/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:20:26 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/11 00:48:05 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_list.h"
#include "utils.h"
#include <stdio.h>

static bool	is_quote(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

static t_token	*extract_word(char **line)
{
	char	*tmp;
	t_token	*token;
	char	quote;

	tmp = *line;
	while (*tmp && is_word(*tmp))
	{
		if (is_quote(*tmp))
		{
			quote = *tmp++;
			while (*tmp && *tmp != quote)
				tmp++;
			if (!*tmp)
			{
				syntax_error();
				return (NULL);
			}
		}
		tmp++;
	}
	token = token_init(ft_substr(*line, 0, tmp - *line), TK_WORD);
	*line = tmp;
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

void	tokenize(t_context *ctx, char *line)
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
			if (!cur->next)
			{
				ctx->sys_error = true;
				ctx->token = head.next;
				return;
			}
			cur = cur->next;
		}
		else if (is_metacharacter(*line))
		{
			cur->next = extract_metacharacter(&line);
			if (!cur->next)
			{
				ctx->sys_error = true;
				ctx->token = head.next;
				return;
			}
			cur = cur->next;
		}
	}
	ctx->token = head.next;
}
