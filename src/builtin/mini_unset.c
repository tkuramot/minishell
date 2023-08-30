/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:48:31 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/29 10:16:50 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 単純に消去すればOK？
#include "builtin.h"

static t_env *serch_env(const char *name, t_env *env_lst)
{
	while(env_lst)
	{
		if(ft_strcmp(env_lst->name, name) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void mini_unset(const t_token *lst, t_env *env_lst)
{
	t_env *delete_env;

	if(!lst || !env_lst)
		return ;
	delete_env = serch_env(lst->word, env_lst);
	env_lst_node_delete(env_lst, delete_env);
}
