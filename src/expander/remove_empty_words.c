/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:32:13 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/14 22:45:55 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"
#include "type.h"

void	rm_head(t_token **lst)
{
	t_token	*buf;
	t_token	*delnode;

	delnode = *lst;
	buf = delnode->next;
	free(delnode);
	*lst = buf;
}

void	rm_empty_words(t_ast *ast)
{
	t_token	*tmp;
	t_token	*delnode;

	if (!ast)
		return ;
	rm_empty_words(ast->right);
	rm_empty_words(ast->left);
	if (!ast->argv)
		return ;
	tmp = ast->argv;
	while (tmp && tmp->next)
	{
		if (!tmp->next->word)
		{
			delnode = tmp->next;
			tmp->next = delnode->next;
			free(delnode);
		}
		else
			tmp = tmp->next;
	}
	tmp = ast->argv;
	if (!tmp->word)
		rm_head(&tmp);
	ast->argv = tmp;
}
