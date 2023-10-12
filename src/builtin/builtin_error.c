/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:27:05 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/12 22:25:52 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	cd_no_such_file(char *command, char *file)
{
	ft_dprintf(1, "minishell: %s: ", command);
	perror(file);
}

void	numeric_error(char *status)
{
	ft_dprintf(STDERR_FILENO, "minishell: exit: ");
	ft_dprintf(STDERR_FILENO, "%s: ", status);
	ft_dprintf(STDERR_FILENO, "numeric argument required\n");
}

void	too_many_error(void)
{
	ft_dprintf(STDERR_FILENO, "minishell: exit: ");
	ft_dprintf(STDERR_FILENO, "too many arguments\n");
}
