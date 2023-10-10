/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:32:13 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/10 02:22:27 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"
#include "type.h"

static t_token	*find_enpty_word(t_context *ctx)
{
	t_token *lst;

	lst = ctx->ast->argv;
	while(lst->next)
	{
		if(ft_strcmp(lst->next->word, "") == 0)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void rm_empty_words(t_context *ctx)
{
	t_token *tmp;
	t_token *head;
	t_token *del_node;

	tmp = ctx->ast->argv;
	head = ctx->ast->argv;
	if(!tmp)
		return ;
	tmp = tmp->next;
	while(tmp)
	{
		if(ft_strcmp(tmp->word, "") == 0)
		{
			del_node = tmp;
			tmp = find_enpty_word(ctx);
			tmp->next = del_node->next;
			free(del_node->word);
			free(del_node);
			ctx->ast->argv = head;
		}
		tmp = tmp->next;
	}
	if(ft_strcmp(head->word, "") == 0)
	{
		del_node = head;
		head = head->next;
		free(del_node->word);
		free(del_node);
	}
	ctx->ast->argv = head;
}
