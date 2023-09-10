/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:03:24 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/10 17:48:10 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"

void	execute_cmd(t_ast *ast, t_env *env_lst)
{
	mini_handle_command(ast->lst, env_lst);
}

void	execute_pipe(t_ast *ast, t_env *env_lst)
{
	int	pipe_fd[2];
	int	pid;
	int	status;

	if (pipe(pipe_fd) == -1)
		fatal_error("pipe");
	pid = fork();
	if (pid == -1)
		fatal_error("fork");
	if (pid == 0)
	{
		close(pipe_fd[P_READ]);
		dup2(pipe_fd[P_WRITE], STDOUT_FILENO);
		execute(ast->left, env_lst);
	}
	wait(&status);
	dup2(pipe_fd[P_READ], STDIN_FILENO);
	close(pipe_fd[P_WRITE]);
	printf("ok\n");
	execute(ast->right, env_lst);
}

void	execute(t_ast *ast, t_env *env_lst)
{
	if (!ast)
		return;
	if (ast->type == ND_PIPE)
		execute_pipe(ast, env_lst);
	if (ast->type == ND_CMD)
		execute_cmd(ast, env_lst);
}
