/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:03:24 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/23 18:56:44 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"

void	execute_pipe(t_ast *ast, t_env *env_lst)
{
	int	pipe_fd[2];
	int	pid;

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
			close(pipe_fd[PIPE_READ]);
			dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
			execute_pipe(ast->left, env_lst);
		}
	}
	else if (ast->type == ND_CMD)
		run_cmd_parent(ast->lst, env_lst);
}

void	execute(t_ast *ast, t_env *env_lst)
{
	int	pid;
	int	status;

	if (!ast)
		return;
	if (ast->type == ND_PIPE)
	{
		pid = fork();
		if (pid == 0)
			execute_pipe(ast, env_lst);
		wait(&status);
	}
	if (ast->type == ND_CMD)
		run_simple_cmd(ast->lst, env_lst);
}
