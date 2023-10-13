/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:52:12 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/12 23:43:50 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

t_token	*token_init(char *word, t_token_type type)
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

t_token	*token_copy(t_token *token)
{
	if (!token)
		return (NULL);
	return (token_init(ft_strdup(token->word), token->type));
}

void	token_lst_free(t_token *lst)
{
	t_token	*buf;

	while (lst)
	{
		buf = lst;
		lst = lst->next;
		free(buf->word);
		free(buf);
	}
}
