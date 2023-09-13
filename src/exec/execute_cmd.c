/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:03:24 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/13 23:10:22 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"

void	execute_pipe(t_ast *ast, t_env *env_lst)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		fatal_error("pipe");
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
