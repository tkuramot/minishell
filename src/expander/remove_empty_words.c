/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:32:13 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/14 22:12:39 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"
#include "type.h"

void	rm_empty_words(t_ast *ast)
{
	t_token	*head;
	t_token	*tmp;
	t_token	*delnode;

	if (!ast)
		return ;
	rm_empty_words(ast->right);
	rm_empty_words(ast->left);
	if (!ast->argv)
		return ;
	head = ast->argv;
	tmp = head;
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
		if (!tmp)
			break ;
	}
	if (!head->word)
	{
		delnode = head;
		head = head->next;
		free(delnode);
	}
	ast->argv = head;
}
