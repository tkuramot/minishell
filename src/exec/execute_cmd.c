/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:03:24 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/14 00:50:30 by tkuramot         ###   ########.fr       */
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
			close(pipe_fd[PIPE_READ]);
			dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
			execute_pipe(ast->left, env_lst);
		}
		else
		{
			close(pipe_fd[PIPE_WRITE]);
			dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
			close(pipe_fd[PIPE_READ]);
			char	**command;
			char	**env;

			command = token_lst_to_array(ast->right->lst);
			env = env_list_to_array(env_lst);
			handle_command(command, env);
		}
	}
	else if (ast->type == ND_CMD)
	{
		char	**command;
		char	**env;

		command = token_lst_to_array(ast->lst);
		env = env_list_to_array(env_lst);
		handle_command(command, env);
	}
}

void	execute(t_ast *ast, t_env *env_lst)
{
	if (!ast)
		return;
	if (ast->type == ND_PIPE)
		execute_pipe(ast, env_lst);
	if (ast->type == ND_CMD)
		mini_handle_command(ast->lst, env_lst);
}
