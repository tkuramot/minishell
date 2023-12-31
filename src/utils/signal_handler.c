/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 08:32:55 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/04 07:42:11 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	idle_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		ft_dprintf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_parent_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		ft_dprintf(STDOUT_FILENO, "\n");
	}
}

void	exec_parent_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
		ft_dprintf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		g_signal = sig;
		ft_dprintf(STDOUT_FILENO, "Quit: 3\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
