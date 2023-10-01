/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:02:32 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/01 22:11:35 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <signal.h>

sig_atomic_t g_signal;

void	fatal_error(char *err);
void	syntax_error(void);
void	print_perror(char *cmd);
void	cmd_not_found_error(char *cmd);
void	set_sig_handler(void);
void	set_default_sig_handler(void);;
void	set_ign_sig_handler(void);
void	set_heredoc_sig_handler(void);
void	sigint_handler(int sig);
void	sigint_heredoc_handler(int sig);
void	sigint_handler_no_prompt(int sig);
void	sigquit_handler(int sig);
int		open_or_create_file(char *file);
int		open_append_file(char *file);


#endif
