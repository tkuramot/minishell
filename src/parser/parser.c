/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/18 23:16:56 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "utils.h"

static bool	expect_pipe(t_token *lst)
{
	if (!lst || !lst->next)
		return (false);
	return (ft_strcmp(lst->next->word, "|") == 0);
}

static bool		add_redirect(t_list **redirect, t_token **lst)
{
	if (!lst || !*lst || !(*lst)->next)
		return (false);
	ft_lstadd_back(redirect, ft_lstnew((*lst)->next->word));
	*lst = (*lst)->next->next;
	return (true);
}

static void		arrange_node(t_ast *ast)
{
	t_token	*lst = ast->lst;
	t_token	*tmp;
	t_token	head;
	t_token	*cur;

	if (!lst)
		return;
	tmp = ast->lst;
	head.next = NULL;
	cur = &head;
	while (tmp)
	{
		if (tmp->type == TK_REDIR_IN && add_redirect(&ast->red_in, &tmp))
			continue;
		else if (tmp->type == TK_REDIR_OUT && add_redirect(&ast->red_out, &tmp))
			continue;
		else if (tmp->type == TK_REDIR_HEREDOC && add_redirect(&ast->red_heredoc, &tmp))
			continue;
		else if (tmp->type == TK_REDIR_APPEND && add_redirect(&ast->red_append, &tmp))
			continue;
		cur->next = tmp;
		cur = cur->next;
		tmp = tmp->next;
	}
	ast->argv = head.next;
}

static t_ast	*parse_cmd(t_token **lst)
{
	t_ast	*node;
	t_token	*cmd;
	t_token	*tmp;

	if (!lst || !*lst)
		return (NULL);
	cmd = *lst;
	tmp = *lst;
	while (tmp->next && !expect_pipe(tmp))
		tmp = tmp->next;
	*lst = tmp->next;
	tmp->next = NULL;
	node = ast_new_node_cmd(cmd);
	arrange_node(node);
	return (node);
}

t_ast	*parse_token(t_token *lst)
{
	t_ast	*node;

	node = parse_cmd(&lst);
	if (!node)
		fatal_error("malloc");
	while (true)
	{
		if (lst && ft_strcmp(lst->word, "|") == 0)
		{
			lst = lst->next;
			node = ast_new_node(ND_PIPE, node, parse_cmd(&lst));
		}
		else
			return (node);
	}
	return (parse_token(lst));
}
