/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:15:39 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/14 11:58:42 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#define FIND_FILE 2

void	env_init(t_context *ctx)
{
	t_env		*head;
	t_env		*new;
	size_t		i;

	i = 0;
	head = env_lst_head();
	if (!head)
		fatal_error("malloc");
	while (environ[i])
	{
		new = env_lst_node_new(environ[i]);
		if (!new)
			fatal_error("malloc");
		env_lst_add_back(head, new);
		i++;
	}
	ctx->env = head;
}

static int	is_env_option(const t_token *lst)
{
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
	return (FIND_FILE);
}

int	mini_env(const t_token *lst, t_env *env_lst)
{
	if (!env_lst)
		return (1);
	while (lst && ft_strcmp("env", lst->word) == 0)
		lst = lst->next;
	if (lst && !is_env_option(lst))
		return (0);
	if (lst && is_env_option(lst) == FIND_FILE)
	{
		errno = 2;
		ft_dprintf(1, "env: ");
		perror(lst->word);
		return (127);
	}
	env_lst = env_lst->next;
	while (env_lst)
	{
		ft_dprintf(STDOUT_FILENO, "%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
	return (0);
}
