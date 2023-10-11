/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:17:32 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 10:55:14 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_lst_add_back(t_env *lst, t_env *new)
{
	if (!lst || !new)
		return ;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

void	env_lst_node_delete(t_env *lst, t_env *delete_node)
{
	t_env	*head;

	head = lst;
	if (!lst || !delete_node)
		return ;
	while (lst && lst->next != delete_node)
		lst = lst->next;
	if (!lst)
		return ;
	lst->next = delete_node->next;
	free(delete_node->name);
	free(delete_node->value);
	free(delete_node);
	lst = head;
}

void	free_all_env_lst(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	free(lst->value);
	free_all_env_lst(lst->next);
	free(lst);
}

size_t	env_lst_size(t_env *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	*env_strjoin(char *name, char *value)
{
	char	*name_equal;
	char	*env_str;

	if (!name || !value)
		return (NULL);
	name_equal = ft_strjoin(name, "=");
	if (!name_equal)
		return (NULL);
	env_str = ft_strjoin(name_equal, value);
	free(name_equal);
	if (!env_str)
		return (NULL);
	return (env_str);
}
