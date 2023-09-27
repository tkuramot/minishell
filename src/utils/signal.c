/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:11:22 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/27 13:06:34 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	signal_handler(int sig, siginfo_t *info, void *ctx)
{
	(void)sig;
	(void)info;
	(void)ctx;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
	}
}

void	set_signal(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &sa, NULL);
}
