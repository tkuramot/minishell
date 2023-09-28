/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:41:27 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/28 22:05:14 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "builtin.h"
# include "lexer.h"

// epander_utils.c
bool	is_identifier_char(char c);
bool	is_expandable(char *str, size_t *i);

// void	str_expander(char **str);
void	env_var_expander(t_ast *ast, t_env *env_lst);

char	*no_quote_expander(char *str, size_t *i, t_env *env_lst);

// single_quote_expander.c
char	*single_quote_expander(char *str, size_t *i);


#endif
