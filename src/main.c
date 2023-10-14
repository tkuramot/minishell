/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:33:13 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/14 18:42:15 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "expander.h"
#include "libft.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	print_minishell(void)
{
	ft_dprintf(STDERR_FILENO,
		"                                   __              ___    ___\n");
	ft_dprintf(STDERR_FILENO,
		"           __          __         /\\ \\            /\\_ \\  /\\_ \\\n");
	ft_dprintf(STDERR_FILENO,
		"  ___ ___ /\\_\\    ___ /\\_\\    ____\\ \\ \\___      __\\//\\ \\ \\//\\ \\\n");
	ft_dprintf(STDERR_FILENO,
		"/' __` __`\\/\\ \\ /' _ `\\/\\ \\  /',__\\\\ \\  _ `\\  /'__`\\\\ \\ \\  \\ \\ \\\n");
	ft_dprintf(STDERR_FILENO,
		"/\\ \\/\\ \\/\\ \\ \\ \\/\\ \\/\\ \\ \\ \\/\\__, `\\\\ \\ \\ \\ \\/\\  __/ \\_\\ \\_ \\_\\ \\_\n");
	ft_dprintf(STDERR_FILENO,
		"\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\/\\____/ \\ \\_\\ \\_\\ \\____\\/\\____\\/\\____\\\n");
	ft_dprintf(STDERR_FILENO,
		" \\/_/\\/_/\\/_/\\/_/\\/_/\\/_/\\/_/\\/___/   \
\\/_/\\/_/\\/____/\\/____/\\/____/\n\n");
}

static void	process_cmd(t_context *ctx, char *line)
{
	if (g_signal == 1)
		ctx->status = g_signal;
	if (g_signal == SIGINT || g_signal == SIGQUIT)
		ctx->status = -g_signal;
	g_signal = 0;
	add_history(line);
	set_exec_parent_sig_handler();
	tokenize(ctx, line);
	parse_token(ctx);
	expand_environ(ctx);
	rm_empty_words(ctx);
	execute(ctx);
}

int	main(void)
{
	char		*line;
	t_context	ctx;

	ft_bzero(&ctx, sizeof (t_context));
	print_minishell();
	env_init(&ctx);
	rl_outstream = stderr;
	while (true)
	{
		ctx.sys_error = false;
		set_idle_sig_handler();
		line = readline("\x1b[32mminishell$ \x1b[0m");
		if (!line)
		{
			ft_dprintf(STDERR_FILENO, "exit\n");
			line = find_env_value("?", &ctx);
			exit(ft_atoi(line));
		}
		if (*line)
			process_cmd(&ctx, line);
		free_cmd_related_malloc(&ctx, &line);
	}
	return (0);
}

/*
__attribute__((destructor)) static void destructor()
{
    system("leaks -q minishell");
}
*/
