/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 23:32:42 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/25 23:32:58 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

#include "parser.h"
#include "libft.h"
#include "exec.h"

// input.c
void	redirect_in_file(char *file);

// output.c
void	redirect_out_file(char *file);
void	redirect_out_apend_file(char *file);

void	redirect(t_ast *ast);

#endif
