/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_operations_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:50:22 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/12 23:35:41 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	*env_lst_head(void)
{
	t_env	*head;

	head = malloc(sizeof(t_env));
	if (!head)
		fatal_error("malloc");
	head->next = NULL;
	head->name = ft_strdup("");
	if (!head->name)
		fatal_error("malloc");
	head->value = ft_strdup("");
	if (!head->value)
		fatal_error("malloc");
	return (head);
}

static t_env	*env_lst_node_new_helper(t_env *new, char *new_env)
{
	char	**env_value;

	env_value = ft_split(new_env, '=');
	if (!env_value)
		return (NULL);
	new->name = env_value[0];
	if (!env_value[1])
	{
		new->value = ft_strdup("");
		if (!new->value)
		{
			free(new->name);
			free(new);
			free(env_value);
			return (NULL);
		}
	}
	else
		new->value = env_value[1];
	free(env_value);
	return (new);
}

t_env	*env_lst_node_new(char *new_env)
{
	t_env	*new;

	if (!new_env)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (env_lst_node_new_helper(new, new_env));
}
