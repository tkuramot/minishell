/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/19 21:32:58 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

typedef enum e_token_type
{
	TK_REDIR_IN = 0,
	TK_REDIR_OUT = 1,
	TK_REDIR_APPEND = 2,
	TK_REDIR_HEREDOC = 3,
	TK_REDIR_HEREDOC_SQ,
	TK_REDIR_HEREDOC_DQ,
	TK_WORD,
	TK_PIPE,
	TK_EOF,
}	t_token_type;

typedef struct s_token	t_token;
struct s_token
{
	char			*word;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
};

t_token	*tokenize(char *line);
bool	is_blank(char c);
bool	is_metacharacter(char c);
bool	start_with(char *s, const char *prefix);
bool	is_word(char c);
void	consume_blank(char **line);
t_token	*token_copy(t_token *token);
void	token_lst_free(t_token *lst);

#endif
