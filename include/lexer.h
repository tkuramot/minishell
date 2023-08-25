/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/25 18:00:17 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define TOKEN_DLM " \t|<>"

# include "libft.h"

typedef enum e_token_type
{
	TOK_GENERAL = -1,
	TOK_PIPE = '|',
	TOK_QUOTE = '\'',
	TOK_DQUOTE = '\"',
	TOK_GREATER = '>',
	TOK_LESS = '<',
}	t_token_type;

typedef enum e_token_state
{
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
	STATE_GENERAL,
}	t_token_state;

typedef struct s_token	t_token;
struct s_token
{
	t_token			*prev;
	t_token			*next;
	t_token_type	type;
	char			*data;
};

typedef struct s_tokenizer
{
	t_token_type	type;
	int64_t			str_i;
	int64_t			tok_i;
	t_token			*cur_token;
	t_token			*token_list;
	t_token_state	state;
}	t_tokenizer;

int	get_char_type(char c);

#endif
