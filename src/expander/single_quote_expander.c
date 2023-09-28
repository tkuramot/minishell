/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_expander.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:43:42 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/28 22:20:16 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*single_quote_expander(char *str, size_t *i)
{
	size_t	start;
	size_t	end;
	char	*ans;

	start = *i + 1;
	end = start;
	while (str[end] != SINGLE_QUOTE && str)
		end++;
	if (str[end] != SINGLE_QUOTE)
		return (NULL);
	ans = ft_substr(str, start, end - start);
	if (!ans)
		return (NULL);
	*i = end;
	return (ans);
}
