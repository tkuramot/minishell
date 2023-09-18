/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/18 22:30:07 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static bool	expect_pipe(t_token *lst)
{
	if (!lst || !lst->next)
		return (false);
	return (ft_strcmp(lst->next->word, "|") == 0);
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
