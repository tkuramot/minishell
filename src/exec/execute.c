/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:03:24 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/24 15:54:29 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"

void	traverse_pipe(int std[2], t_ast *ast, t_env *env_lst, t_list **proc_lst)
{
	pid_t	pid;
	int		pp[2];
	int		tmp;

	if (!ast)
		return;
	if (ast->type == ND_PIPE)
	{
		if (pipe(pp) == -1)
			fatal_error("pipe");
		tmp = std[0];
		std[0] = pp[0];
		traverse_pipe(std, ast->right, env_lst, proc_lst);
		close(pp[0]);
		std[0] = tmp;
		std[1] = pp[1];
		traverse_pipe(std, ast->left, env_lst, proc_lst);
		close(pp[1]);
	}
	else if (ast->type == ND_CMD)
	{
		pid = fork();
		if (pid == 0)
		{
			run_cmd_parent(ast->lst, env_lst);
		}
		ft_lstadd_front(proc_lst, ft_lstnew(ft_itoa(pid)));
	}
}

static int	wait_all_children(t_list *proc_lst)
{
	t_list	*tmp;
	pid_t	pid;
	int		status;

	tmp = proc_lst;
	while(ft_lstsize(tmp) > 1)
	{
		pid = ft_atoi(tmp->content);
		waitpid(pid, &status, 0);
		tmp = tmp->next;
	}
	pid = ft_atoi(tmp->content);
	waitpid(pid, &status, 0);
	return (status);
}

int	execute(t_ast *ast, t_env *env_lst)
{
	t_list *proc_lst;
	int		status;
	int		std[2];

	proc_lst = NULL;
	if (!ast)
		return (1);
	if (ast->type == ND_PIPE)
	{
		std[0] = 0;
		std[1] = 1;
		traverse_pipe(std, ast, env_lst, &proc_lst);
		status = wait_all_children(proc_lst);
		return (status);
	}
	if (ast->type == ND_CMD)
		return (run_simple_cmd(ast->lst, env_lst));
	return (0);
}
