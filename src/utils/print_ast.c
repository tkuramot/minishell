/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:30:17 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/14 22:31:41 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_ast(t_ast *ast)
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
	print_ast(ast->left);
	print_ast(ast->right);
}
