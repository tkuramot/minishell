/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/14 17:19:10 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_string.h"
#include "lexer.h"
#include "utils.h"

static t_ast	*handle_syntax_error(t_context *ctx, t_ast *node)
{
	syntax_error();
	ctx->sys_error = true;
	ctx->status = 258;
	return (node);
}

static t_ast	*parse_cmd(t_context *ctx, t_token **lst)
{
	t_token	head;
	t_token	*tmp;

	head.next = NULL;
	tmp = &head;
	if (!lst || !*lst)
		return (NULL);
	if (expect(*lst, TK_PIPE))
	{
		syntax_error();
		return (NULL);
	}
	while (true)
	{
		if (!*lst || expect(*lst, TK_PIPE))
			break ;
		if (is_redirect(*lst) && !expect((*lst)->next, TK_WORD))
			return (handle_syntax_error(ctx,
					arrange_node(ctx, ast_new_node_cmd(head.next))));
		tmp->next = token_copy(*lst);
		*lst = (*lst)->next;
		tmp = tmp->next;
	}
	if (!head.next)
		return (handle_syntax_error(ctx,
				arrange_node(ctx, ast_new_node_cmd(head.next))));
	return (arrange_node(ctx, ast_new_node_cmd(head.next)));
}

void	parse_token(t_context *ctx)
{
	t_token	*lst;
	t_ast	*right;

	lst = ctx->token;
	ctx->ast = parse_cmd(ctx, &lst);
	if (!ctx->ast)
		ctx->sys_error = true;
	if (ctx->sys_error)
		return ;
	while (true)
	{
		if (lst && expect(lst, TK_PIPE))
		{
			lst = lst->next;
			right = parse_cmd(ctx, &lst);
			if (!right)
				handle_syntax_error(ctx, NULL);
			else
				ctx->ast = ast_new_node(ND_PIPE, ctx->ast, right);
			if (ctx->sys_error)
				return ;
		}
		else
			return ;
	}
}
