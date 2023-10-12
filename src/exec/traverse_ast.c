/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:58:30 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/12 22:07:40 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"
#include "utils.h"

static void	traverse_ast_pipe_node(int std[2],
				t_context *ctx, t_list **fd, t_list **proc_lst);
static void	traverse_ast_cmd_node(int std[2],
				t_context *ctx, t_list **fd, t_list **proc_lst);

void	traverse_ast(int std[2], t_context *ctx, t_list **fd, t_list **proc_lst)
{
	if (!ctx->ast)
		return ;
	if (ctx->ast->type == ND_PIPE)
		traverse_ast_pipe_node(std, ctx, fd, proc_lst);
	else if (ctx->ast->type == ND_CMD)
		traverse_ast_cmd_node(std, ctx, fd, proc_lst);
}

static void	traverse_ast_pipe_node(int std[2],
				t_context *ctx, t_list **fd, t_list **proc_lst)
{
	t_ast	*tmp_ast;
	int		pp[2];
	int		tmp;

	if (pipe(pp) == -1)
	{
		perror("pipe");
		ctx->sys_error = true;
		return ;
	}
	ft_lstadd_back(fd, ft_lstnew(ft_itoa(pp[0])));
	ft_lstadd_back(fd, ft_lstnew(ft_itoa(pp[1])));
	tmp = std[0];
	std[0] = pp[0];
	tmp_ast = ctx->ast;
	ctx->ast = tmp_ast->right;
	traverse_ast(std, ctx, fd, proc_lst);
	close(pp[0]);
	std[0] = tmp;
	std[1] = pp[1];
	ctx->ast = tmp_ast->left;
	traverse_ast(std, ctx, fd, proc_lst);
	close(pp[1]);
}

static void	traverse_ast_cmd_node(int std[2],
				t_context *ctx, t_list **fd, t_list **proc_lst)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ctx->sys_error = true;
	}
	if (pid == 0)
	{
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
		if (!redirect(ctx->ast))
			exit(127);
		ft_lstclear(fd, clear_fd);
		run_simple_cmd_parent(&ctx->ast->argv, ctx->env);
	}
	ft_lstadd_front(proc_lst, ft_lstnew(ft_itoa(pid)));
}
