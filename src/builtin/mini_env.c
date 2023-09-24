/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:15:39 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/24 11:14:54 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <errno.h>

// envの順番はソートしたほうが多分いい.後でやる
t_env	*env_lst_init(void)
{
	extern char	**environ;
	t_env		*head;
	t_env		*new;
	size_t		i;

	i = 0;
	head = env_lst_node_new(environ[i]);
	if (!head)
		return (NULL);
	while (environ[++i])
	{
		new = env_lst_node_new(environ[i]);
		if (!new)
		{
			// freeかくのだりいいいいいい
			return (NULL);
		}
		env_lst_add_back(head, new);
	}
	return (head);
}

static bool	is_env_option(const t_token *lst)
{
	errno = 2;
	while (lst && ft_strcmp("env", lst->word) == 0)
		lst = lst->next;
	if (!lst)
		return (true);
	if (ft_strncmp("--", lst->word, 2) == 0)
	{
		if (ft_strlen(lst->word) == 2)
			return (true);
		return (false);
	}
	if (ft_strcmp("-", lst->word) == 0)
		return (false);
	perror(lst->word);
	return (false);
}

int	mini_env(const t_token *lst, t_env *env_lst)
{
	if (!env_lst)
		return (1);
	if (lst && !is_env_option(lst))
		return (1);
	while (env_lst)
	{
		ft_dprintf(STDOUT_FILENO, "%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
	return (0);
}
