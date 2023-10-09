/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:17:32 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/04 22:42:00 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include <stdlib.h>

t_env	*env_lst_node_new(char *new_env)
{
	t_env	*new;
	char	**env_value;

	if (!new_env)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		fatal_error("malloc");
	new->next = NULL;
	env_value = ft_split(new_env, '=');
	if (!env_value)
		fatal_error("malloc");
	new->name = env_value[0];
	if (!env_value[1])
	{
		new->value = ft_strdup("");
		// new->value = NULL;
		if (!new->value)
		{
			free(new->name);
			free(new);
			fatal_error("malloc");
		}
	}
	else
		new->value = env_value[1];
	free(env_value);
	return (new);
}

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
