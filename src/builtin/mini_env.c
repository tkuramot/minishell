/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:15:39 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/30 23:29:56 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env *env_lst_init(void)
{
	extern char	**environ;
	t_env	*head;
	t_env	*new;
	size_t i;

	i = 0;
	head = env_lst_node_new(environ[i]);
	if(!head)
		return (NULL);
	while(environ[++i])
	{
		// printf("%s\n", environ[i]);
		new = env_lst_node_new(environ[i]);
		if(!new)
		{
			// freeかくのだりいいいいいい
			return (NULL);
		}
		// printf("%s\n", new->name);
		env_lst_add_back(head, new);
	}
	return (head);
}

void mini_env(const t_env *env_lst)
{
	if(!env_lst)
		return;
	while(env_lst)
	{
		printf("%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
}
