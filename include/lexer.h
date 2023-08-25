/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/25 21:02:12 by tkuramot         ###   ########.fr       */
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
	t_token			*lst;
	t_token_state	state;
}	t_tokenizer;

t_token	*make_token_list(char *line);
int		get_char_type(char c);
void	init_tokenizer(t_tokenizer *tokenizer);
void	extract_token(char *line, t_tokenizer *tokenizer);
void	tokenize_general(char *line, t_tokenizer *tokenizer);
void	tokenize_dquote(char *line, t_tokenizer *tokenizer);
void	tokenize_quote(char *line, t_tokenizer *tokenizer);
t_token	*token_new(t_token_type type, char *data);
t_token	*token_get_back(t_token *lst);
void	token_add_back(t_token **lst, t_token *token);

#endif
