/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:52:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/13 00:39:28 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*resolve_path(char *cmd, char *path_env)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	i = 0;
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (is_executable(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	free_two_d_array(paths);
	return (NULL);
}
