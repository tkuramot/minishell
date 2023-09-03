/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:28:13 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/03 18:41:23 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*ast_new_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof (t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*ast_new_node_cmd(t_token *lst)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof (t_ast));
	if (!node)
		return (NULL);
	node->type = ND_CMD;
	node->lst = lst;
	return (node);
}
