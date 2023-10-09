/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:10:58 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/09 18:47:24 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "heredoc.h"
#include "utils.h"

static bool	redir_in(t_list *node)
{
	int	fd;
	char	*tmp;

	fd = open(((t_redirect *)node->content)->file, O_RDONLY);
	if (fd == -1)
	{
		tmp = ft_strjoin("minishell: ", ((t_redirect *)node->content)->file);
		perror(tmp);
		free(tmp);
		return (false);
	}
	dup2(fd, STDIN_FILENO);
	return (true);
}

static bool	redir_out(t_list *node)
{
	int	fd;
	char	*tmp;

	fd = open_or_create_file(((t_redirect *)node->content)->file);
	if (fd == -1)
	{
		tmp = ft_strjoin("minishell: ", ((t_redirect *)node->content)->file);
		perror(tmp);
		free(tmp);
		return (false);
	}
	dup2(fd, STDOUT_FILENO);
	return (true);
}

static bool	redir_append(t_list *node)
{
	int	fd;
	char	*tmp;

	fd = open_append_file(((t_redirect *)node->content)->file);
	if (fd == -1)
	{
		tmp = ft_strjoin("minishell: ", ((t_redirect *)node->content)->file);
		perror(tmp);
		free(tmp);
		return (false);
	}
	dup2(fd, STDOUT_FILENO);
	return (true);
}

static bool	redir_heredoc(t_list *node)
{
	return (redir_in(node));
}

bool	redirect(t_ast *node)
{
	t_list	*cur;

	cur = node->redir_lst;
	while (cur)
	{
		if (((t_redirect *)cur->content)->type == TK_REDIR_IN)
			if (!redir_in(cur))
				return (false);
		if (((t_redirect *)cur->content)->type == TK_REDIR_OUT)
			if (!redir_out(cur))
				return (false);
		if (((t_redirect *)cur->content)->type == TK_REDIR_APPEND)
			if (!redir_append(cur))
				return (false);
		if (((t_redirect *)cur->content)->type == TK_REDIR_HEREDOC)
			if (!redir_heredoc(cur))
				return (false);
		cur = cur->next;
	}
	return (true);
}
