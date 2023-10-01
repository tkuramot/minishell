/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 08:32:55 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/01 22:19:02 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return;
	g_signal = 1;
	ft_dprintf(STDOUT_FILENO, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


void	sigint_heredoc_handler(int sig)
{
	if (sig != SIGINT)
		return;
	g_signal = 1;
	ft_dprintf(STDOUT_FILENO, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_no_prompt(int sig)
{
	if (sig != SIGINT)
		return;
	g_signal = SIGINT;
	ft_dprintf(STDOUT_FILENO, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return;
	g_signal = sig;
	ft_dprintf(STDOUT_FILENO, "Quit: 3\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}
