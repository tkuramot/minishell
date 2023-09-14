/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:20:26 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/10 21:03:58 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <stdio.h>

static t_token	*token_init(char *word, t_token_type type)
{
	t_token	*token;

	if (!word)
		fatal_error("malloc");
	token = ft_calloc(1, sizeof (t_token));
	if (!token)
		fatal_error("malloc");
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
	token = token_init(ft_substr(tmp, 0, i), TK_WORD);
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
	token = token_init(word, TK_OP);
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

// リークが残って気になったので勝手に作りました。
void	token_lst_free(t_token *lst)
{
	t_token	*buf;

	while(lst)
	{
		buf = lst;
		free(lst->word);
		lst = lst->next;
		free(buf);
	}
}
