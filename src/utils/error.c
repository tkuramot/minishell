/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:59:15 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/14 18:35:22 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

void	fatal_error(char *err)
{
	ft_dprintf(STDERR_FILENO, "%s\n", err);
	exit(1);
}

void	syntax_error(t_context *ctx)
{
	ctx->status = 258;
	ctx->sys_error = true;
	ft_dprintf(STDERR_FILENO, "minishell: syntax error\n");
}

void	print_perror(char *cmd)
{
	ft_dprintf(STDERR_FILENO, "minishell: ");
	perror(cmd);
	exit(1);
}

void	perror_exit(char *cmd, int status)
{
	ft_dprintf(STDERR_FILENO, "minishell: ");
	perror(cmd);
	exit(status);
}

void	cmd_not_found_error(char *cmd)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd);
	exit(127);
}
