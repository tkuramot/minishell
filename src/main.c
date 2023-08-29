/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:33:13 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/28 22:35:07 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int	main(void)
{
	extern char	**environ;
	char	*line;
	t_token	*lst;
	t_token	*buf;
	t_env	*env_lst;

	env_lst = env_lst_init();
	while (true)
	{
		line = readline("\x1b[32mminishell$ \x1b[0m");
		if (!line)
			return (1);
		if (*line)
			add_history(line);
		lst = tokenize(line);
		buf = lst;
		while (lst)
		{
			printf("[%s]\n", lst->word);
			lst = lst->next;
		}
		mini_handle_command(buf, env_lst); //exit処理(仮)
		free(line);
	}
	return (0);
}
