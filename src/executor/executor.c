/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:51:37 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/09 18:22:20 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	execute_cmd(t_ast *ast)
{
	t_token	*lst;

	if (!ast)
		return ;
ft_dprintf(STDOUT_FILENO, "=========\n");
ft_dprintf(STDOUT_FILENO, "NODE TYPE is %d\n", ast->type);
	lst = ast->lst;
	while (lst)
	{
	ft_dprintf(STDOUT_FILENO, "[%s]\n", lst->word);
		lst = lst->next;
	}
	execute_cmd(ast->left);
	execute_cmd(ast->right);
}
