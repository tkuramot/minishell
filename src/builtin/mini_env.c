/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:15:39 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/09 18:23:56 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <errno.h>


// env---
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
		new = env_lst_node_new(environ[i]);
		if(!new)
		{
			// freeかくのだりいいいいいい
			return (NULL);
		}
		env_lst_add_back(head, new);
	}
	return (head);
}

static bool	is_env_option(char *option)
{
	errno = 2;
	if(ft_strncmp("--", option, 2) == 0)
	{
		if(ft_strlen(option) == 2)
			return (true);
		return (false);
	}
	if(ft_strcmp("-", option) == 0)
		return (false);
	perror(option); //errno使わない場合どう表示させるんや。。。
	return (false);
}

void mini_env(const t_token *lst, t_env *env_lst)
{
	if(!env_lst)
		return;
	if(lst && !is_env_option(lst->word))
		return ;
	while(env_lst)
	{
	ft_dprintf(STDOUT_FILENO, "%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
}
