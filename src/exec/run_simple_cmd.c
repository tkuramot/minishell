/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:22:12 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/25 11:44:43 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"
#include "exec.h"

int	run_simple_cmd(t_token *lst, t_env *env_lst)
{
	if (ft_strcmp(lst->word, "exit") == 0)
		return (mini_exit(lst, env_lst));
	else if (ft_strcmp(lst->word, "pwd") == 0)
		return (mini_pwd());
	else if (ft_strcmp(lst->word, "cd") == 0)
		return (mini_cd(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "env") == 0)
		return (mini_env(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "unset") == 0)
		return (mini_unset(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "export") == 0)
		return (mini_export(lst->next, env_lst));
	else if (ft_strcmp(lst->word, "echo") == 0)
		return (mini_echo(lst->next));
	else
		return (run_cmd_child(lst, env_lst));
}

// Run all commands including builtins in child procs
int	run_simple_cmd_child(t_token *lst, t_env *env_lst)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strcmp(lst->word, "exit") == 0)
			mini_exit(lst, env_lst);
		else if (ft_strcmp(lst->word, "pwd") == 0)
			mini_pwd();
		else if (ft_strcmp(lst->word, "cd") == 0)
			mini_cd(lst->next, env_lst);
		else if (ft_strcmp(lst->word, "env") == 0)
			mini_env(lst->next, env_lst);
		else if (ft_strcmp(lst->word, "unset") == 0)
			mini_unset(lst->next, env_lst);
		else if (ft_strcmp(lst->word, "export") == 0)
			mini_export(lst->next, env_lst);
		else if (ft_strcmp(lst->word, "echo") == 0)
			mini_echo(lst->next);
		else
			run_cmd_parent(lst, env_lst);
	}
	waitpid(pid, &status, 0);
	return (status);
}
