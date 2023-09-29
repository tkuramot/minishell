/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:15:39 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/29 12:40:54 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include <errno.h>

// envの順番はソートしたほうが多分いい.後でやる
void	env_init(t_context *ctx)
{
	t_env		*head;
	t_env		*new;
	size_t		i;

	i = 0;
	head = env_lst_node_new(environ[i]);
	if (!head)
		fatal_error("malloc");
	while (environ[++i])
	{
		new = env_lst_node_new(environ[i]);
		if (!new)
			fatal_error("malloc");
		env_lst_add_back(head, new);
	}
	ctx->env = head;
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
