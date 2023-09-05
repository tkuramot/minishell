/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:47:24 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/05 23:44:31 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_env(char *env_str)
{
	size_t	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
	{
		if (!(ft_isalnum(env_str[i]) || env_str[i] == '_'))
			return (0);
		i++;
	}
	if (env_str[i] == '\0')
		return (0);
	return (1);
}

size_t	find_first_equals_index(char *env_str)
{
	size_t	i;

	i = 0;
	while (env_str[i] != '=')
		i++;
	return (i);
}

int	duplication(char *env_str, t_env *env_lst)
{
	size_t	i;

	i = find_first_equals_index(env_str);
	while (env_lst)
	{
		if (ft_strncmp(env_str, env_lst->name, i) == 0
			&& find_first_equals_index(env_str) == ft_strlen(env_lst->name))
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(&env_str[i + 1]);
			if (!env_lst->value)
				return (0);
			return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

void	mini_export(t_token *token_lst, t_env *env_lst)
{
	t_env	*new;

	if (!token_lst)
		return ;
	if (!is_env(token_lst->word))
		return ;
	if (duplication(token_lst->word, env_lst))
		return ;
	new = env_lst_node_new(token_lst->word);
	env_lst_add_back(env_lst, new);
}
