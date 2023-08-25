/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:07:18 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/25 18:32:42 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_new(t_token_type type, char *data)
{
	t_token	*token;

	token = ft_calloc(1, sizeof (t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->data = data;
	return (token);
}

t_token	*token_get_back(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	token_add_back(t_token **lst, t_token *token)
{
	t_token	*last_token;

	if (!lst)
		return;
	if (!*lst)
	{
		*lst = token;
		return;
	}
	last_token = token_get_back(*lst);
	last_token->next = token;
	token->prev = last_token;
}
