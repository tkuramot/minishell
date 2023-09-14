/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/14 22:18:55 by tkuramot         ###   ########.fr       */
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
		&& !exepect_next(lst, STR_REDIRECT_IN)
		&& !exepect_next(lst, STR_REDIRECT_OUT));
}

static t_ast	*extract_cmd(t_token **lst)
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

t_ast	*parse_token(t_token *lst)
{
	t_ast	*node;

	node = extract_cmd(&lst);
	if (!node)
		fatal_error("malloc");
	while (true)
	{
		if (lst && ft_strcmp(lst->word, STR_PIPE) == 0)
		{
			lst = lst->next;
			node = ast_new_node(ND_PIPE, node, extract_cmd(&lst));
		}
		else
			return (node);
	}
}
