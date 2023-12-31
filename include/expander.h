/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:41:27 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/14 22:24:17 by tsishika         ###   ########.fr       */
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
char	*find_env_value(char *name, t_context *ctx);

// epander_utils.c
bool	is_identifier_char_flag(char c, int *flag);
bool	is_identifier_char(char c);
bool	is_expandable(char *str, size_t *i);
char	*extend_str(char *left, char *right);

// expander.c
void	str_expander(char **str, t_context *ctx);
void	env_var_expander(t_ast *ast, t_context *ctx);

// quote_handling.c
void	expand_environ(t_context *ctx);
char	*single_quote_expander(char *str, size_t *i, t_context *ctx);
char	*no_quote_expander(char *str, size_t *i, t_context *ctx);
char	*double_quote_expander(char *str, size_t *i, t_context *ctx);

// redirect_filename_expander.c
void	redirect_filename_expander(char **str);

// remove_empty_words.c
void	rm_empty_words(t_ast *ast);

// word_splitting.c
void	word_split(t_token **token_lst);

#endif
