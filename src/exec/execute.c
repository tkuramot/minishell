/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:03:24 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/01 22:51:32 by tsishika         ###   ########.fr       */
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

void	traverse_pipe(int std[2], t_list *fd, t_ast *ast, t_env *env, t_list **proc_lst)
{
	pid_t	pid;
	int		pp[2];
	int		tmp;

	if (!ast)
		return ;
	if (ast->type == ND_PIPE)
	{
		if (pipe(pp) == -1)
			fatal_error("pipe");
		ft_lstadd_back(&fd, ft_lstnew(ft_itoa(pp[0])));
		ft_lstadd_back(&fd, ft_lstnew(ft_itoa(pp[1])));
		tmp = std[0];
		std[0] = pp[0];
		traverse_pipe(std, fd, ast->right, env, proc_lst);
		close(pp[0]);
		std[0] = tmp;
		std[1] = pp[1];
		traverse_pipe(std, fd, ast->left, env, proc_lst);
		close(pp[1]);
	}
	else if (ast->type == ND_CMD)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(std[0], STDIN_FILENO);
			dup2(std[1], STDOUT_FILENO);
			if (!redirect(ast))
			{
				//TODO ctx->status = 1
				return;
			}
			ft_lstclear(&fd, clear_fd);
			run_simple_cmd_parent(ast->argv, env);
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
	while (ft_lstsize(tmp) > 1)
	{
		pid = ft_atoi(tmp->content);
		waitpid(pid, &status, 0);
		tmp = tmp->next;
	}
	pid = ft_atoi(tmp->content);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	execute(t_context *ctx)
{
	t_list	*proc_lst;
	t_list	*fd;
	t_ast	*tmp;
	int		std[2];

	proc_lst = NULL;
	fd = NULL;
	if (!ctx->ast)
		return;
	if (ctx->ast->type == ND_PIPE)
	{
		std[0] = 0;
		std[1] = 1;
		tmp = ctx->ast;
		traverse_pipe(std, fd, ctx->ast, ctx->env, &proc_lst);
		ctx->ast = tmp;
		ctx->status = wait_all_children(proc_lst);
	}
	if (ctx->ast->type == ND_CMD)
	{
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		if (!redirect(ctx->ast))
		{
			//TODO ctx->status = 1
			return;
		}
		ctx->status = run_simple_cmd(ctx->ast->argv, ctx->env);
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
	}
}
