/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:57:17 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/27 15:55:28 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metacharacter(char c)
{
	return (c && ft_strchr("|&<> \t\n", c));
}

bool	start_with(char *s, const char *prefix)
{
	return (ft_strncmp(s, prefix, ft_strlen(prefix)) == 0);
}

bool	is_word(char c)
{
	return (c && !is_metacharacter(c));
}

void	consume_blank(char **line)
{
	if (is_blank(**line))
		(*line)++;
}
