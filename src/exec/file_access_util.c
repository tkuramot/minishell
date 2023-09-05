/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:29:56 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/04 16:35:22 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_executable(char *command)
{
	if (access(command, X_OK) == -1)
		return (0);
	return (1);
}

int	is_readable(char *file)
{
	if (access(file, F_OK) == -1)
		return (0);
	if (access(file, R_OK) == -1)
		return (0);
	return (1);
}
