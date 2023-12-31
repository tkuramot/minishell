/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:20:26 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/14 18:36:35 by tkuramot         ###   ########.fr       */
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

// Set sys error in caller func when malloc fails
static t_token	*extract_word(t_context *ctx, char **line)
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
				syntax_error(ctx);
				return (NULL);
			}
		}
		tmp++;
	}
	token = token_init(ft_substr(*line, 0, tmp - *line), TK_WORD);
	*line = tmp;
	return (token);
}

// Set sys error in caller func when malloc fails
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
			if (!word)
				return (NULL);
			break ;
		}
		i++;
	}
	*line += ft_strlen(ops[i]);
	return (token_init(word, token_type[i]));
}

static void	handle_sys_error(t_context *ctx, t_token *lst)
{
	ctx->sys_error = true;
	ctx->token = lst;
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
			cur->next = extract_word(ctx, &line);
			if (!cur->next)
				return (handle_sys_error(ctx, head.next));
			cur = cur->next;
		}
		else if (is_metacharacter(*line))
		{
			cur->next = extract_metacharacter(&line);
			if (!cur->next)
				return (handle_sys_error(ctx, head.next));
			cur = cur->next;
		}
	}
	ctx->token = head.next;
}
