/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 01:09:00 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/29 01:22:24 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env *decompress(t_token *lst, t_env *env_lst)
{
	char *name;

	name = &lst->word[1];
	while(env_lst)
	{
		if(ft_strcmp(name, env_lst->name) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}
