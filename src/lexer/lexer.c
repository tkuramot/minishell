/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:20:26 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/25 21:37:30 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

t_token	*make_token_list(char *line)
{
	t_tokenizer	tokenizer;
	int64_t		i;

	init_tokenizer(&tokenizer);
	i = tokenizer.str_i + tokenizer.tok_i;
	while (line[i])
	{
		//printf("[%lld]\n", tokenizer.str_i);
		tokenizer.type = get_char_type(line[i]);
		if (tokenizer.state == STATE_GENERAL)
			tokenize_general(line, &tokenizer);
		else if (tokenizer.state == STATE_IN_DQUOTE)
			tokenize_dquote(line, &tokenizer);
		else if (tokenizer.state == STATE_IN_QUOTE)
			tokenize_quote(line, &tokenizer);
		i = tokenizer.str_i + tokenizer.tok_i;
	}
	return (tokenizer.lst);
}
