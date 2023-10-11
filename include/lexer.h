/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/11 08:23:09 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

# include "libft.h"
# include "type.h"
# include <stdbool.h>
# include <stdio.h>

void	tokenize(t_context *ctx, char *line);
bool	is_blank(char c);
bool	is_metacharacter(char c);
bool	start_with(char *s, const char *prefix);
bool	is_word(char c);
bool	consume_blank(char **line);
t_token	*token_init(char *word, t_token_type type);
t_token	*token_copy(t_token *token);
void	token_lst_free(t_token *lst);

#endif
