/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:59:15 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/30 19:54:07 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

void	fatal_error(char *err)
{
	ft_dprintf(STDERR_FILENO, "%s\n", err);
	exit(1);
}

void	syntax_error(void)
{
	ft_dprintf(STDERR_FILENO, "minishell: syntax error\n");
}

void	print_perror(char *cmd)
{
	ft_dprintf(STDERR_FILENO, "minishell: ");
	perror(cmd);
	exit(1);
}

void	cmd_not_found_error(char *cmd)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd);
	exit(127);
}
