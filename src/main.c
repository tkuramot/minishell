/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:33:13 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/03 18:21:24 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

void	execute_cmd(t_ast *ast)
{
	t_token	*lst;

	if (!ast)
		return ;
	printf("=========\n");
	lst = ast->lst;
	while (lst)
	{
		printf("[%s]\n", lst->word);
		lst = lst->next;
	}
	execute_cmd(ast->left);
	execute_cmd(ast->right);
}

int	main(void)
{
	char	*line;
	t_token	*lst;
	t_token	*tmp;
	t_ast	*ast;

	while (true)
	{
		line = readline("\x1b[32mminishell$ \x1b[0m");
		if (!line)
			return (1);
		if (*line)
			add_history(line);
		lst = tokenize(line);
		tmp = lst;
		while (lst)
		{
			printf("[%s]\n", lst->word);
			lst = lst->next;
		}
		ast = parse_token(tmp);
		execute_cmd(ast);
		free(line);
	}
	return (0);
}
