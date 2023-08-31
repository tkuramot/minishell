/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 01:09:00 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/31 13:44:34 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	*decompress(char *env_name, t_env *env_lst)
{
	char	*name;

	name = &env_name[1];
	while (env_lst)
	{
		if (ft_strcmp(name, env_lst->name) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}
