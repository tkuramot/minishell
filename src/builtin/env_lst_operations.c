/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:17:32 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/29 01:57:37 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>

t_env *env_lst_node_new(char *new_env)
{
	t_env *new;
	char **env_value;

	if(!new_env)
		return (NULL);
	new = malloc(sizeof(t_env));
	if(!new)
		return (NULL);
	new->next = NULL;
	env_value = ft_split(new_env, '=');
	if(!env_value){
		free(new);
		return (NULL);
	}
	new->name = env_value[0];
	if(!env_value[1]){
		new->value = ft_strdup("");
		if(new->value){
			// free(env_value); splitのfree処理描くのだるい。
			free(new->name);
			free(new);
			return (NULL);
		}
	}
	else
		new->value = env_value[1];
	return (new);
}

void env_lst_add_back(t_env *lst, t_env *new)
{
	if (!lst || !new)
		return ;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

void env_lst_node_delete(t_env *lst, t_env *delete_node)
{
	t_env *head;

	head = lst;
	if(!lst || !delete_node)
		return ;
	while(lst && lst->next != delete_node)
		lst = lst->next;
	if(!lst)
		return ;
	// printf("1lst->next = %s\n", lst->next->name);
	lst->next = delete_node->next;
	// printf("2lst->next = %s\n", lst->next->name);
	free(delete_node->name);
	free(delete_node->value);
	free(delete_node);
	lst = head;
}
