/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:02:32 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/27 16:32:09 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	fatal_error(char *err);
void	syntax_error(char *location);
void	print_perror(char *cmd);
void	cmd_not_found_error(char *cmd);
void	set_default_sig_handler(void);
void	set_child_sig_handler(void);;

#endif
