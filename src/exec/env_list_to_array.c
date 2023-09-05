/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:30:33 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/05 15:38:22 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

char	**env_list_to_array(t_env *env_lst)
{
	size_t	i;
	size_t	lst_size;
	char	**env_array;
	char	*buf;

	i = 0;
	lst_size = env_lst_size(env_lst);
	env_array = malloc(sizeof(char *) * (lst_size + 1));
	if (!env_array)
		return (NULL);
	while (env_lst)
	{
		buf = ft_strjoin(env_lst->name, "=");
		if (!buf)
			return (NULL);
		env_array[i] = ft_strjoin(buf, env_lst->value);
		if (!env_array[i])
			return (NULL);
		free(buf);
		env_lst = env_lst->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_env_array(char **env_array)
{
	size_t	i;

	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
