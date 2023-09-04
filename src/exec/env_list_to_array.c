/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:30:33 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/04 13:11:21 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

// char	**env_list_to_array(t_env *env_lst)
// {
// 	size_t	i;
// 	size_t	lst_cnt;
// 	char	*env_equal;
// 	char	**env_array;

// 	lst_cnt = env_lst_size(env_lst);
// 	env_array = malloc(sizeof(char) * (lst_cnt + 1));
// 	if (!env_array)
// 		return (NULL);
// 	i = 0;
// 	while (env_lst)
// 	{
// 		env_equal = ft_strjoin(env_lst->name, "=");
// 		if (!env_equal)
// 			return (NULL);
// 		env_array[i] = ft_strjoin(env_equal, env_lst->value);
// 		printf("%zu~~%s\n", i, env_array[i]);
// 		if (!env_array[i])
// 			return (NULL);
// 		free(env_equal);
// 		i++;
// 		env_lst = env_lst->next;
// 	}
// 	env_array[i] = NULL;
// 	return (env_array);
// }


char	**env_list_to_array(t_env *env_lst)
{
	size_t i = 0;
	size_t lst_size = env_lst_size(env_lst);
	char **env_array;
	char *buf;

	env_array = malloc(sizeof(char *) * (lst_size + 1));
	if(!env_array)
		return (NULL);
	while(env_lst)
	{
		buf = ft_strjoin(env_lst->name, "=");
		if(!buf)
			return (NULL);
		env_array[i] = ft_strjoin(buf, env_lst->value);
		if(!env_array[i])
			return (NULL);
		free(buf);
		env_lst = env_lst->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
