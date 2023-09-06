/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:51:37 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/03 18:52:07 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	execute_cmd(t_ast *ast)
{
	t_token	*lst;

	if (!ast)
		return ;
	printf("=========\n");
	printf("NODE TYPE is %d\n", ast->type);
	lst = ast->lst;
	while (lst)
	{
		printf("[%s]\n", lst->word);
		lst = lst->next;
	}
	execute_cmd(ast->left);
	execute_cmd(ast->right);
}
