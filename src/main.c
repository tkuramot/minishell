/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:33:13 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/19 21:30:47 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

static void	print_minishell(void)
{
	ft_dprintf(STDERR_FILENO, "                                   __              ___    ___\n");
	ft_dprintf(STDERR_FILENO, "           __          __         /\\ \\            /\\_ \\  /\\_ \\\n");
	ft_dprintf(STDERR_FILENO, "  ___ ___ /\\_\\    ___ /\\_\\    ____\\ \\ \\___      __\\//\\ \\ \\//\\ \\\n");
	ft_dprintf(STDERR_FILENO, "/' __` __`\\/\\ \\ /' _ `\\/\\ \\  /',__\\\\ \\  _ `\\  /'__`\\\\ \\ \\  \\ \\ \\\n");
	ft_dprintf(STDERR_FILENO, "/\\ \\/\\ \\/\\ \\ \\ \\/\\ \\/\\ \\ \\ \\/\\__, `\\\\ \\ \\ \\ \\/\\  __/ \\_\\ \\_ \\_\\ \\_\n");
	ft_dprintf(STDERR_FILENO, "\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\/\\____/ \\ \\_\\ \\_\\ \\____\\/\\____\\/\\____\\\n");
	ft_dprintf(STDERR_FILENO, " \\/_/\\/_/\\/_/\\/_/\\/_/\\/_/\\/_/\\/___/   \\/_/\\/_/\\/____/\\/____/\\/____/\n\n");
}

int	main(void)
{
	char	*line;
	t_token	*lst;
	t_ast	*ast;
	extern char	**environ;
	t_env		*env_lst;

	print_minishell();
	env_lst = env_lst_init();
	rl_outstream = stderr;
	while (true)
	{
		line = readline("\x1b[32mminishell$ \x1b[0m");
		if (!line)
			return (1);
		if (*line)
		{
			add_history(line);
			lst = tokenize(line);
			ast = parse_token(lst);
			# if DEBUG == 1
			(void)env_lst;
			printf("REDIRECT IN >\n");
			while (ast->redir_lst)
			{
				int red_type = (int)((t_redirect *)(ast->redir_lst->content))->type;
				printf("file [%s]",
						(char *)((t_redirect *)(ast->redir_lst->content))->file);
				if (red_type == TK_REDIR_IN)
					printf(" / type [IN]\n");
				if (red_type == TK_REDIR_OUT)
					printf(" / type [OUT]\n");
				if (red_type == TK_REDIR_APPEND)
					printf(" / type [APPEND]\n");
				if (red_type == TK_REDIR_HEREDOC)
					printf(" / type [HEREDOC]\n");
				ast->redir_lst = ast->redir_lst->next;
			}
			printf("ARGV >\n");
			while (ast->argv)
			{
				printf("[%s]\n", ast->argv->word);
				ast->argv = ast->argv->next;
			}

			# else
			execute(ast, env_lst);
			free(line);
			token_lst_free(lst);
			# endif
		}
	}
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q minishell");
// }
