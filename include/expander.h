/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:41:27 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/29 01:53:11 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "builtin.h"
# include "lexer.h"


// expander_handling.c
char	*expand_env_string(char	*str, size_t *i, t_env *env_lst);

// epander_utils.c
bool	is_identifier_char(char c);
bool	is_expandable(char *str, size_t *i);

// expander.c
void	env_var_expander(t_ast *ast, t_env *env_lst);

// quote_handling.c
char	*single_quote_expander(char *str, size_t *i);
char	*no_quote_expander(char *str, size_t *i, t_env *env_lst);
char	*double_quote_expander(char *str, size_t *i, t_env *env_lst);

#endif
