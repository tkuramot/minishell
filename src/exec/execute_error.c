/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 22:48:41 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/25 23:04:12 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
