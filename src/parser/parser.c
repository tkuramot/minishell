/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/29 16:52:29 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_string.h"
#include "lexer.h"
#include "utils.h"

static t_ast	*parse_cmd(t_token **lst)
{
	t_ast	*node;
	t_token	*cmd;
	t_token	*tmp;

	if (!lst || !*lst)
		return (NULL);
	cmd = *lst;
	tmp = *lst;
	while (tmp->next && !expect(tmp->next, TK_PIPE))
		tmp = tmp->next;
	*lst = tmp->next;
	tmp->next = NULL;
	node = ast_new_node_cmd(cmd);
	arrange_node(node);
	return (node);
}

void	parse_token(t_context *ctx)
{
	t_token	*lst;
	t_ast	*left;
	t_ast	*right;

	lst = ctx->token;
	left = parse_cmd(&lst);
	if (!left)
		fatal_error("malloc");
	while (true)
	{
		if (lst && expect(lst, TK_PIPE))
		{
			lst = lst->next;
			right = parse_cmd(&lst);
			left = ast_new_node(ND_PIPE, left, right);
		}
		else
		{
			ctx->ast = left;
			return;
		}
	}
}
