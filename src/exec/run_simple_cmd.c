/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:22:12 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 14:43:06 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"
#include "exec.h"
#include "expander.h"

int	run_simple_cmd(t_token **token_lst, t_env *env_lst)
{
	t_token	*lst;

	lst = *token_lst;
	// env_lstがNULLの場合って環境変数がない時ですが、/bin/lsやechoなどはじっそうできるべきだからいらなそうこの条件
	if (!lst)
		return (0);
	if (ft_strcmp(lst->word, "export") == 0)
		return (mini_export(lst->next, env_lst));
	else
	{
		word_split(&lst);
		token_lst_free(*token_lst);
		*token_lst = lst;
		if (ft_strcmp(lst->word, "exit") == 0)
			return (mini_exit(lst->next, env_lst));
		else if (ft_strcmp(lst->word, "pwd") == 0)
			return (mini_pwd());
		else if (ft_strcmp(lst->word, "cd") == 0)
			return (mini_cd(lst->next, env_lst));
		else if (ft_strcmp(lst->word, "env") == 0)
			return (mini_env(lst->next, env_lst));
		else if (ft_strcmp(lst->word, "unset") == 0)
			return (mini_unset(lst->next, env_lst));
		else if (ft_strcmp(lst->word, "echo") == 0)
			return (mini_echo(lst->next));
		else
			return (run_non_builtin_child(lst, env_lst));
	}
}

void	run_simple_cmd_parent(t_token *lst, t_env *env_lst)
{
	if (!lst)
		return ;
	if (ft_strcmp(lst->word, "exit") == 0)
		exit(mini_exit(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "pwd") == 0)
		exit(mini_pwd());
	else if (ft_strcmp(lst->word, "cd") == 0)
		exit(mini_cd(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "env") == 0)
		exit(mini_env(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "unset") == 0)
		exit(mini_unset(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "export") == 0)
		exit(mini_export(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "echo") == 0)
		exit(mini_echo(lst->next));
	else
		run_non_builtin_parent(lst, env_lst);
}
