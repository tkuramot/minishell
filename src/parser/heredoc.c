/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:20:57 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/03 23:31:26 by tkuramot         ###   ########.fr       */
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
		quote_handle_heredoc(fd, del, ctx);
	else
		handle_heredoc(fd, del);
	ft_lstadd_back(redirect, ft_lstnew(init_redir(tmp_file, TK_REDIR_HEREDOC)));
	if (g_signal != 0)
		ctx->status = 1;
	close(fd);
	return (tmp_file);
}
