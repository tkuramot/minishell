/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_filename_expander.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 05:05:45 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/04 05:16:35 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*redirect_double_quote_expander(char *str, size_t *i)
{
	size_t	start;
	size_t	end;
	char	*ans;

	start = *i + 1;
	end = start;
	while (str[end] != DOUBLE_QUOTE && str)
		end++;
	if (str[end] != DOUBLE_QUOTE)
		return (NULL);
	ans = ft_substr(str, start, end - start);
	if (!ans)
		return (NULL);
	*i = end;
	return (ans);
}

char	*redirect_no_quote_expander(char *str, size_t *i)
{
	size_t	end;
	char	*left;
	char	*right;

	end = *i;
	left = ft_strdup("");
	while (str[end] && str[end] != SINGLE_QUOTE && str[end] != DOUBLE_QUOTE)
	{
		right = ft_substr(str, end, 1);
		if (!right)
		{
			free(left);
			return (NULL);
		}
		left = extend_str(left, right);
		if (!left)
			return (NULL);
		end++;
	}
	*i = end - 1;
	return (left);
}

void	redirect_filename_expander(char **str)
{
	char	*buf_str;
	char	*sub;
	char	*first;
	char	*ans;
	size_t	i;

	buf_str = *str;
	i = 0;
	first = ft_strdup("");
	while (buf_str[i])
	{
		if (buf_str[i] == SINGLE_QUOTE)
			sub = single_quote_expander(*str, &i);
		else if (buf_str[i] == DOUBLE_QUOTE)
			sub = redirect_double_quote_expander(*str, &i);
		else
			sub = redirect_no_quote_expander(*str, &i);
		ans = ft_strjoin(first, sub);
		free(first);
		free(sub);
		first = ans;
		i++;
	}
	*str = first;
}
