/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:43:42 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/14 22:22:25 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*single_quote_expander(char *str, size_t *i, t_context *ctx)
{
	size_t	start;
	size_t	end;
	char	*ans;

	ctx->include_quote = true;
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

char	*no_quote_expander(char *str, size_t *i, t_context *ctx)
{
	size_t	end;
	char	*left;
	char	*right;

	end = *i;
	left = ft_strdup("");
	while (str[end] && str[end] != SINGLE_QUOTE && str[end] != DOUBLE_QUOTE)
	{
		if (str[end] == '$')
			right = expand_env_string(str, &end, ctx);
		else
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

char	*double_quote_expander(char *str, size_t *i, t_context *ctx)
{
	size_t	end;
	char	*left;
	char	*right;

	ctx->include_quote = true;
	end = *i + 1;
	left = ft_strdup("");
	while (str[end] && str[end] != DOUBLE_QUOTE)
	{
		if (str[end] == '$')
			right = expand_env_string(str, &end, ctx);
		else
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
	*i = end;
	return (left);
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
