/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/03 18:29:07 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

typedef enum e_token_type
{
	TK_WORD,
	TK_OP,
	TK_EOF
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

void	token_lst_free(t_token *lst);

#endif
