/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:03:24 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/24 13:37:06 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"

void	traverse_pipe(t_ast *ast, t_env *env_lst, t_list **proc_lst)
{
	pid_t	pid;
	int	pipe_fd[2];
	int	out_fd;

	if (!ast)
		return;
	if (ast->type == ND_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			fatal_error("pipe");
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fd[PIPE_WRITE]);
			dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
			close(pipe_fd[PIPE_READ]);
			run_cmd_parent(ast->right->lst, env_lst);
		}
		else
		{
			dprintf(STDERR_FILENO, "pid for cmd [%s] [%d]\n", ast->right->lst->word, pid);
			ft_lstadd_front(proc_lst, ft_lstnew(ft_itoa(pid)));
			out_fd = dup(STDOUT_FILENO);
			close(pipe_fd[PIPE_READ]);
			dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
			close(pipe_fd[PIPE_WRITE]);
			traverse_pipe(ast->left, env_lst, proc_lst);
			dup2(out_fd, STDOUT_FILENO);
		}
	}
	else if (ast->type == ND_CMD)
	{
		close(pipe_fd[PIPE_READ]);
		close(pipe_fd[PIPE_WRITE]);
		pid = fork();
		if (pid == 0)
			run_cmd_parent(ast->lst, env_lst);
		dprintf(STDERR_FILENO, "pid for cmd [%s] %d\n", ast->lst->word, pid);
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

	proc_lst = NULL;
	if (!ast)
		return (1);
	if (ast->type == ND_PIPE)
	{
		traverse_pipe(ast, env_lst, &proc_lst);
		status = wait_all_children(proc_lst);
		return (status);
	}
	if (ast->type == ND_CMD)
		return (run_simple_cmd(ast->lst, env_lst));
	return (0);
}
