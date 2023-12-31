/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 21:05:51 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 17:20:53 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	is_expandable(char *str, size_t *i)
{
	size_t	end;
	size_t	cnt;

	cnt = 0;
	end = *i;
	while (str[end] == '$')
	{
		end++;
		cnt++;
	}
	if (str[end] == '\0')
		return (false);
	*i = end - 1;
	if (cnt % 2 == 0)
		return (false);
	return (true);
}

bool	is_identifier_char_flag(char c, int *flag)
{
	if (*flag == 1)
		return (false);
	else
	{
		if (c == '?')
			*flag = 1;
		return (c == '_' || ('A' <= c && c <= 'Z') || c == '?'
			|| ('a' <= c && c <= 'z') || ('0' <= c && c <= '9'));
	}
}

bool	is_identifier_char(char c)
{
	return (c == '_' || ('A' <= c && c <= 'Z') || c == '?'
		|| ('a' <= c && c <= 'z') || ('0' <= c && c <= '9'));
}

char	*extend_str(char *left, char *right)
{
	char	*buf;

	buf = left;
	left = ft_strjoin(buf, right);
	free(buf);
	free(right);
	return (left);
}
