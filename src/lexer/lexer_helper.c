/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:34:46 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/25 17:55:18 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_char_type(char c)
{
	if (c == TOK_PIPE)
		return (TOK_PIPE);
	if (c == TOK_DQUOTE)
		return (TOK_DQUOTE);
	if (c == TOK_QUOTE)
		return (TOK_QUOTE);
	return (TOK_GENERAL);
}
