/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 20:43:11 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/25 21:34:44 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void init_tokenizer(t_tokenizer *tokenizer)
{
	ft_bzero(tokenizer, sizeof (t_tokenizer));
	tokenizer->state = STATE_GENERAL;
}

void	extract_token(char *line, t_tokenizer *tokenizer)
{
	t_token	*token;

	token = token_new(tokenizer->type,
				ft_substr(line, tokenizer->str_i, tokenizer->tok_i));
	token_add_back(&tokenizer->lst, token);
	tokenizer->str_i += tokenizer->tok_i;
	tokenizer->tok_i = 0;
}

void	tokenize_general(char *line, t_tokenizer *tokenizer)
{
	(void)line;
	if (tokenizer->type == TOK_DQUOTE)
	{
		tokenizer->state = STATE_IN_DQUOTE;
		tokenizer->tok_i++;
	}
	/*
	else if (tokenizer->type == TOK_QUOTE)
		tokenizer->tok_i++;
	else if (tokenizer->type == TOK_PIPE)
		tokenizer->tok_i++;
	*/
}

void	tokenize_dquote(char *line, t_tokenizer *tokenizer)
{
	if (tokenizer->type == TOK_DQUOTE)
	{
		extract_token(line, tokenizer);
		tokenizer->state = STATE_GENERAL;
	}
	else
		tokenizer->tok_i++;
}

void	tokenize_quote(char *line, t_tokenizer *tokenizer)
{
	if (tokenizer->type == TOK_QUOTE)
	{
		extract_token(line, tokenizer);
		tokenizer->state = STATE_GENERAL;
	}
	else
		tokenizer->tok_i++;
}
