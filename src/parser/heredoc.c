/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:20:57 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/04 04:59:21 by tsishika         ###   ########.fr       */
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
	set_heredoc_sig_handler();
	if (ft_strchr(tmp_file, '\'') || ft_strchr(tmp_file, '\"'))
		quote_handle_heredoc(fd, del);
	else
		handle_heredoc(fd, del, ctx);
	ft_lstadd_back(redirect, ft_lstnew(init_redir(tmp_file, TK_REDIR_HEREDOC, ctx)));
	if (g_signal != 0)
		ctx->sys_error = true;
	close(fd);
	return (tmp_file);
}
