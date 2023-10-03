/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/03 23:05:59 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_string.h"
#include "lexer.h"
#include "utils.h"

static t_ast	*parse_cmd(t_context *ctx, t_token **lst)
{
	t_token	*cmd;
	t_token	*tmp;

	if (!lst || !*lst)
		return (NULL);
	tmp = *lst;
	while (true)
	{
		if (is_redirect(tmp) && !expect(tmp->next, TK_WORD))
		{
			syntax_error();
			ctx->status = 1;
			return (NULL);
		}
		if (!tmp->next || expect(tmp->next, TK_PIPE))
			break;
		tmp = tmp->next;
	}
	cmd = *lst;
	*lst = tmp->next;
	tmp->next = NULL;
	return (arrange_node(ctx, ast_new_node_cmd(cmd)));
}

void	parse_token(t_context *ctx)
{
	t_token	*lst;
	t_ast	*right;

	if (ctx->status != 0)
		return;
	lst = ctx->token;
	ctx->ast = parse_cmd(ctx, &lst);
	if (!ctx->ast)
		ctx->status = 1;
	if (ctx->status != 0)
		return;
	while (true)
	{
		if (lst && expect(lst, TK_PIPE))
		{
			lst = lst->next;
			right = parse_cmd(ctx, &lst);
			if (!right)
				ctx->status = 1;
			if (ctx->status != 0)
				return;
			ctx->ast = ast_new_node(ND_PIPE, ctx->ast, right);
		}
		else
			return;
	}
}
