/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:10:58 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/30 09:07:32 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

bool	redir_in(t_list *node)
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

bool	redir_out(t_list *node)
{
	int	fd;
	char	*tmp;

	printf("ok\n");
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
		cur = cur->next;
	}
	return (true);
}
