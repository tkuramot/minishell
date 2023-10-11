/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:02:32 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/11 14:04:18 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "type.h"
# include <signal.h>

sig_atomic_t	g_signal;

void	fatal_error(char *err);
void	syntax_error(void);
void	print_perror(char *cmd);
void	perror_exit(char *cmd, int status);
void	cmd_not_found_error(char *cmd);
void	set_idle_sig_handler(void);
void	set_exec_parent_sig_handler(void);
void	set_exec_child_sig_handler(void);;
void	set_heredoc_parent_sig_handler(void);
void	set_heredoc_child_sig_handler(void);
void	idle_sig_handler(int sig);
void	exec_parent_sig_handler(int sig);
void	heredoc_parent_sig_handler(int sig);
int		open_or_create_file(char *file);
int		open_append_file(char *file);
void	free_cmd_related_malloc(t_context *ctx, char **line);

#endif
