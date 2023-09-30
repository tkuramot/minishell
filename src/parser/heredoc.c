/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:20:57 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/01 00:47:26 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "parser.h"
#include "utils.h"

char	*read_heredoc(t_context *ctx, char *del, t_list **redirect)
{
	char	*tmp_file;
	int		fd;

	tmp_file = create_heredoc_file();
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		fatal_error("open");
	if (ft_strchr(tmp_file, '\'') || ft_strchr(tmp_file, '\"'))
		quote_handle_heredoc(fd, del, ctx);
	else
		handle_heredoc(fd, del);
	ft_lstadd_back(redirect, ft_lstnew(init_redir(tmp_file, TK_REDIR_HEREDOC)));
	close(fd);
	return (tmp_file);
}
