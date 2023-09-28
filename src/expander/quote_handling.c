/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:43:42 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/29 01:59:38 by tsishika         ###   ########.fr       */
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

char	*no_quote_expander(char *str, size_t *i, t_env *env_lst)
{
	size_t	end;
	char	*buf1;
	char	*buf2;
	char	*join;

	end = *i;
	buf1 = ft_strdup("");
	while (str[end] && str[end] != SINGLE_QUOTE && str[end] != DOUBLE_QUOTE)
	{
		if (str[end] == '$')
			buf2 = expand_env_string(str, &end, env_lst);
		else
			buf2 = ft_substr(str, end, 1);
		if (!buf2)
		{
			free(buf1);
			return (NULL);
		}
		join = ft_strjoin(buf1, buf2);
		free(buf1);
		free(buf2);
		if(!join)
			return (NULL);
		buf1 = join;
		end++;
	}
	*i = end - 1;
	return (buf1);
}



char	*double_quote_expander(char *str, size_t *i, t_env *env_lst)
{
	size_t	end;
	char	*buf1;
	char	*buf2;
	char	*join;

	end = *i + 1;
	buf1 = ft_strdup("");
	while (str[end] && str[end] != DOUBLE_QUOTE)
	{
		if (str[end] == '$')
			buf2 = expand_env_string(str, &end, env_lst);
		else
			buf2 = ft_substr(str, end, 1);
		if (!buf2)
		{
			free(buf1);
			return (NULL);
		}
		join = ft_strjoin(buf1, buf2);
		free(buf1);
		free(buf2);
		if(!join)
			return (NULL);
		buf1 = join;
		end++;
	}
	*i = end;
	return (buf1);
}

// int main(void)
// {
// 	char *str = "$HOME$$$HOME";
// 	size_t	i = 0;
// 	char *name;
// 	t_env *env_lst;

// 	env_lst = env_lst_init();
// 	ft_dprintf(1, "%d, %s\n", i, str);
// 	name = no_quote_expander(str, &i, env_lst);
// 	ft_dprintf(1, "%d, %s\n", i, name);
// }
