/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:41:27 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/01 22:29:04 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "builtin.h"
# include "lexer.h"
# include "exec.h"
# include "libft.h"
# include <stdlib.h>

// expander_handling.c
char	*expand_env_string(char	*str, size_t *i, t_context *ctx);

// epander_utils.c
bool	is_identifier_char(char c, int *flag);
bool	is_expandable(char *str, size_t *i);
char	*extend_str(char *left, char *right);

// expander.c
void	env_var_expander(t_ast *ast, t_context *ctx);

// quote_handling.c
void	expand_environ(t_context *ctx);
char	*single_quote_expander(char *str, size_t *i);
char	*no_quote_expander(char *str, size_t *i, t_context *ctx);
char	*double_quote_expander(char *str, size_t *i, t_context *ctx);

#endif
