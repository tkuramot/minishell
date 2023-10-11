/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:29:56 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 14:34:14 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/types.h>
#include <sys/stat.h>

int	is_executable(char *command)
{
	if (access(command, F_OK) == -1)
		return (0);
	if (access(command, X_OK) == -1)
		return (0);
	return (1);
}

int	is_directory(char *command)
{
	struct stat	stat_buf;

	if (stat(command, &stat_buf) == -1)
		return (-1);
	if ((stat_buf.st_mode & S_IFMT) == S_IFDIR)
	{
		errno = IS_A_DIRECTORY;
		return (0);
	}
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
