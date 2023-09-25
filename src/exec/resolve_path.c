/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:52:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/25 11:07:18 by tsishika         ###   ########.fr       */
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
