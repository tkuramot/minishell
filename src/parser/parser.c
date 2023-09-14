/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/15 00:15:19 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static bool	exepect_next(t_token *lst, char *op)
{
	if (!lst || !lst->next)
		return (false);
	return (ft_strcmp(lst->next->word, op) == 0);
}

static bool	exepect_next_simple_token(t_token *lst)
{
	if (!lst || !lst->next)
		return (false);
	return (!exepect_next(lst, STR_PIPE)
		&& !exepect_next(lst, STR_REDIR_IN)
		&& !exepect_next(lst, STR_REDIR_OUT)
		&& !exepect_next(lst, STR_HEREDOC)
		&& !exepect_next(lst, STR_REDIR_OUT_AP));
}

static t_ast	*extract_cmd_node(t_token **lst)
{
	t_token	*cmd;
	t_token	*tmp;

	if (!lst || !*lst)
		return (NULL);
	cmd = *lst;
	tmp = *lst;
	while (exepect_next_simple_token(tmp))
		tmp = tmp->next;
	*lst = tmp->next;
	tmp->next = NULL;
	return (ast_new_node_cmd(cmd));
}

static t_ast	*extract_special_node(t_ast *node, t_token **lst,
						t_node_type type)
{
	*lst = (*lst)->next;
	if (type == ND_PIPE)
		return (ast_new_node(ND_PIPE, node, extract_cmd_node(lst)));
	else if (type == ND_REDIR_IN)
		return (ast_new_node(ND_REDIR_IN, node, extract_cmd_node(lst)));
	else if (type == ND_REDIR_OUT)
		return (ast_new_node(ND_REDIR_OUT, node, extract_cmd_node(lst)));
	else if (type == ND_HEREDOC)
		return (ast_new_node(ND_HEREDOC, node, extract_cmd_node(lst)));
	else if (type == ND_REDIR_OUT_AP)
		return (ast_new_node(ND_REDIR_OUT_AP, node, extract_cmd_node(lst)));
	return (NULL);
}

t_ast	*parse_token(t_token *lst)
{
	t_ast	*node;

	if (lst && lst->type == TK_OP)
		node = NULL;
	else
	{
		node = extract_cmd_node(&lst);
		if (!node)
			fatal_error("malloc");
	}
	while (true)
	{
		if (lst && ft_strcmp(lst->word, STR_PIPE) == 0)
			node = extract_special_node(node, &lst, ND_PIPE);
		else if (lst && ft_strcmp(lst->word, STR_REDIR_IN) == 0)
			node = extract_special_node(node, &lst, ND_REDIR_IN);
		else if (lst && ft_strcmp(lst->word, STR_REDIR_OUT) == 0)
			node = extract_special_node(node, &lst, ND_REDIR_OUT);
		else if (lst && ft_strcmp(lst->word, STR_HEREDOC) == 0)
			node = extract_special_node(node, &lst, ND_HEREDOC);
		else if (lst && ft_strcmp(lst->word, STR_REDIR_OUT_AP) == 0)
			node = extract_special_node(node, &lst, ND_REDIR_OUT_AP);
		else
			return (node);
	}
}
