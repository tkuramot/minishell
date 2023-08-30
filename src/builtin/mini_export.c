/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:47:24 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/29 21:00:27 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// やること
// 重複の確認
// 環境変数にできる文字かどうか
// ＝の有無


// 環境変数名に使用可能なのは、アルファベット、数字、_。


#include "builtin.h"

int is_env(char *env_str)
{
	size_t i = 0;
	while(env_str[i] && env_str[i] != '=')
	{
		if(!(ft_isalnum(env_str[i]) || env_str[i] == '_'))
			return (0);
		i++;
	}
	if(env_str[i] == '\0')
		return (0);
	return (1);
}

int find_equals_index(char *env_str)
{
	size_t i;

	i = 0;
	while(env_str[i] != '=')
		i++;
	return (i);
}

int	duplication(t_token *lst, t_env *env_lst)
{
	int i;

	i = find_equals_index(lst->word);
	while(env_lst)
	{
		if(ft_strncmp(lst->word, env_lst->name, i) == 0)
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(&lst->word[i + 1]);
			return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

void	mini_export(t_token *lst, t_env *env_lst)
{
	t_env *new;

	if(!lst)
		return ;
	if(!is_env(lst->word))
		return ;
	if(duplication(lst, env_lst))
		return ;
	new = env_lst_node_new(lst->word);
	env_lst_add_back(env_lst, new);
}
