/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:47:24 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/04 19:53:35 by tsishika         ###   ########.fr       */
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

static void	export_print(t_env *env)
{
	while (env)
	{
		ft_dprintf(1, "declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}

int	mini_export(t_token *token, t_env *env)
{
	t_env	*new;

	if (!token || ft_strcmp(token->word, "") == 0)
	{
		export_print(env);
		return (0);
	}
	while (token)
	{
		if (!is_env(token->word))
			return (0);
		if (duplication(token->word, env))
			return (0);
		new = env_lst_node_new(token->word);
		env_lst_add_back(env, new);
		token = token->next;
	}
	return (0);
}
