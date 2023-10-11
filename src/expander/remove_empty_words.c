/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:32:13 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 17:06:03 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"
#include "type.h"

static t_token	*find_enpty_word(t_context *ctx)
{
	t_token	*lst;

	lst = ctx->ast->argv;
	while (lst->next)
	{
		if (ft_strcmp(lst->next->word, "") == 0)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

static void	free_delnode(t_token **tmp)
{
	free((*tmp)->word);
	free(*tmp);
}

void	move_empty_node(t_token **tmp, t_token **del_node, t_context *ctx)
{
	t_token	*buf_tmp;
	t_token	*del_node_buf;

	buf_tmp = *tmp;
	del_node_buf = buf_tmp;
	buf_tmp = find_enpty_word(ctx);
	buf_tmp->next = del_node_buf->next;
	*tmp = buf_tmp;
	*del_node = del_node_buf;
}

void	rm_empty_words(t_context *ctx)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*del_node;

	if (!ctx->ast || ctx->sys_error || !ctx->ast->argv)
		return ;
	tmp = ctx->ast->argv->next;
	head = ctx->ast->argv;
	while (tmp)
	{
		if (ft_strcmp(tmp->word, "") == 0)
		{
			move_empty_node(&tmp, &del_node, ctx);
			free_delnode(&del_node);
			ctx->ast->argv = head;
		}
		tmp = tmp->next;
	}
	if (ft_strcmp(head->word, "") == 0)
	{
		del_node = head;
		head = head->next;
		free_delnode(&del_node);
	}
	ctx->ast->argv = head;
}
