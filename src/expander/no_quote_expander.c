/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:42:43 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/28 23:31:53 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*find_env_value(char *name, t_env *env_lst)
{
	char	*ans;

	while (env_lst)
	{
		if (ft_strcmp(name, env_lst->name) == 0)
		{
			ans = ft_strdup(env_lst->value);
			return (ans);
		}
		env_lst = env_lst->next;
	}
	ans = ft_strdup("");
	return(ans);
}

char	*get_env_value(char *str, size_t *i, t_env *env_lst)
{
	size_t	start;
	size_t	end;
	char	*search_name;
	char	*ans;

	start = *i;
	end = start;
	while (str[end] && is_identifier_char(str[end]))
		end++;
	search_name = ft_substr(str, start, end - start);
	if (!search_name)
		return (NULL);
	ans = find_env_value(search_name, env_lst);
	free(search_name);
	if (!ans)
		return (NULL);
	*i = end - 1;
	return (ans);
}

char	*concatenate_env(char *str, size_t start, size_t *i, t_env *env_lst)
{
	char	*buf1;
	char	*buf2;
	char	*join;
	size_t	end;

	end = *i + 1;
	buf1 = ft_substr(str, start, end - 1);
	if (!buf1)
		return (NULL);
	buf2 = get_env_value(str, &end, env_lst);
	if (!buf2)
	{
		free(buf1);
		return (NULL);
	}
	join = ft_strjoin(buf1, buf2);
	if (!join)
		return (NULL);
	free(buf1);
	free(buf2);
	*i = end;
	return (join);
}

char	*expand_env_string(char	*str, size_t *i, t_env *env_lst)
{
	size_t	end;
	char	*ans;

	end = *i;
	if (is_expandable(str, &end))
		ans = concatenate_env(str, *i, &end, env_lst);
	else
		ans = ft_substr(str, *i, end - *i + 1);
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
		join = ft_strjoin(buf1, buf2);
		free(buf1);
		free(buf2);
		buf1 = join;
		end++;
	}
	*i = end;
	return (buf1);
}
