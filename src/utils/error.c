/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:59:15 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/26 00:49:57 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

void	fatal_error(char *err)
{
	ft_dprintf(STDERR_FILENO, "%s\n", err);
	exit(1);
}

void	syntax_error(char *location)
{
	ft_dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
}

void	print_perror(char *cmd)
{
	ft_dprintf(STDERR_FILENO, "minishell: ");
	perror(cmd);
	exit(0);
}

void	cmd_not_found_error(char *cmd)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", cmd);
	exit(0);
}
