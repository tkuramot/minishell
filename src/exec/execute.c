/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:03:24 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/11 15:01:06 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"

void	clear_fd(void *content)
{
	int	fd;

	fd = ft_atoi((char *)content);
	close(fd);
	free(content);
}

static int	wait_all_children(t_list *proc_lst)
{
	t_list	*tmp;
	pid_t	pid;
	int		status;

	tmp = proc_lst;
	while (ft_lstsize(tmp) > 1)
	{
		pid = ft_atoi(tmp->content);
		if (waitpid(pid, &status, 0) == -1)
			waitpid(pid, &status, 0);
		tmp = tmp->next;
	}
	pid = ft_atoi(tmp->content);
	if (waitpid(pid, &status, 0) == -1)
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

static void	execute_cmd_with_pipe(t_context *ctx)
{
	t_ast	*tmp;
	int		std[2];
	t_list	*proc_lst;
	t_list	*fd;

	proc_lst = NULL;
	fd = NULL;
	std[0] = 0;
	std[1] = 1;
	tmp = ctx->ast;
	traverse_ast(std, ctx, &fd, &proc_lst);
	ft_lstclear(&fd, clear_fd);
	ctx->ast = tmp;
	ctx->status = wait_all_children(proc_lst);
	ft_lstclear(&proc_lst, free);
	ft_lstclear(&fd, free);
}

static void	execute_simple_cmd(t_context *ctx)
{
	int		std[2];

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	if (!redirect(ctx->ast))
	{
		ctx->status = 1;
		return ;
	}
	ctx->status = run_simple_cmd(&ctx->ast->argv, ctx->env);
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
}

void	execute(t_context *ctx)
{
	if (ctx->sys_error || !ctx->ast)
		return ;
	if (ctx->ast->type == ND_PIPE)
		execute_cmd_with_pipe(ctx);
	if (ctx->ast->type == ND_CMD)
		execute_simple_cmd(ctx);
}
