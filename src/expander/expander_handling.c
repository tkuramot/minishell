/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:42:43 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/04 03:44:49 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

static char	*find_env_value(char *name, t_context *ctx)
{
	char	*ans;
	t_env	*env;

	env = ctx->env;
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
		{
			ans = ft_strdup(env->value);
			return (ans);
		}
		env = env->next;
	}
	if(ft_strcmp(name, "\?") == 0)
	{
		// if(g_signal == SIGINT || g_signal == SIGQUIT)
		// 	ans = ft_itoa(128 + g_signal);
		// else if(g_signal != 0)
		// 	ans = ft_itoa(g_signal);
		// else
		// 	ans = ft_itoa(ctx->status);
		if(ctx->status < 0)
			ans = ft_itoa(128 - ctx->status);
		else
			ans = ft_itoa(ctx->status);
		return(ans);
	}
	ans = ft_strdup("");
	return (ans);
}

static char	*get_env_value(char *str, size_t *i, t_context *ctx)
{
	size_t	start;
	size_t	end;
	int		flag;
	char	*search_name;
	char	*ans;

	start = *i;
	end = start;
	flag = 0;
	while (str[end] && is_identifier_char(str[end], &flag))
		end++;
	search_name = ft_substr(str, start, end - start);
	if (!search_name)
		return (NULL);
	ans = find_env_value(search_name, ctx);
	free(search_name);
	if (!ans)
		return (NULL);
	*i = end - 1;
	return (ans);
}

static char	*concatenate_env(char *str, size_t start, size_t *i, t_context *ctx)
{
	char	*buf1;
	char	*buf2;
	char	*join;
	size_t	end;

	end = *i + 1;
	buf1 = ft_substr(str, start, end - start - 1);
	if (!buf1)
		return (NULL);
	buf2 = get_env_value(str, &end, ctx);
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

char	*expand_env_string(char	*str, size_t *i, t_context *ctx)
{
	size_t	end;
	char	*ans;

	end = *i;
	if (is_expandable(str, &end))
		ans = concatenate_env(str, *i, &end, ctx);
	else
		ans = ft_substr(str, *i, end - *i + 1);
	*i = end;
	return (ans);
}
