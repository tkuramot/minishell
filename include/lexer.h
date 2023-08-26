/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/27 07:01:09 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

typedef enum e_token_type
{
	TK_COMMAND,
	TK_PIPE,
	TK_EOF
} t_token_type;

typedef struct s_token	t_token;
struct s_token
{
	char	*word;
	t_token_type	type;
	t_token			*next;
};

#endif
