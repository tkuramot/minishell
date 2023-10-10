/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/10 13:03:03 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_string.h"
#include "lexer.h"
#include "utils.h"

static t_ast	*parse_cmd(t_context *ctx, t_token **lst)
{
	t_token	head;
	t_token	*tmp;

	head.next = NULL;
	tmp = &head;
	if (!lst || !*lst || expect(*lst, TK_PIPE))
	{
		syntax_error();
		ctx->sys_error = true;
		ctx->status = 258;
		return (NULL);
	}
	while (true)
	{
		if (!*lst || expect(*lst, TK_PIPE))
			break;
		if (is_redirect(*lst) && !expect((*lst)->next, TK_WORD))
		{
			syntax_error();
			ctx->sys_error = true;
			ctx->status = 258;
			return (NULL);
		}
		tmp->next = token_copy(*lst);
		*lst = (*lst)->next;
		tmp = tmp->next;
	}
	return (arrange_node(ctx, ast_new_node_cmd(head.next)));
}

void	parse_token(t_context *ctx)
{
	t_token	*lst;
	t_ast	*right;

	if (ctx->sys_error)
		return;
	lst = ctx->token;
	ctx->ast = parse_cmd(ctx, &lst);
	if (!ctx->ast)
		ctx->sys_error = true;
	if (ctx->sys_error)
		return;
	while (true)
	{
		if (lst && expect(lst, TK_PIPE))
		{
			lst = lst->next;
			right = parse_cmd(ctx, &lst);
			if (!right)
				ctx->sys_error = true;
			if (ctx->sys_error)
				return;
			ctx->ast = ast_new_node(ND_PIPE, ctx->ast, right);
		}
		else
			return;
	}
}
