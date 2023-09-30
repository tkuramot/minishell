/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 23:32:42 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/30 09:02:35 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "parser.h"
# include "libft.h"

void	redirect_in_file(char *file);
void	redirect_out_file(char *file);
void	redirect_out_apend_file(char *file);
bool	redirect(t_ast *ast);

#endif
