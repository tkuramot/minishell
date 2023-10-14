/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:42:36 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/14 22:55:17 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_concatenate(char *str, t_context *ctx)
{
	size_t	i;
	char	*ans;
	char	*sub;
	char	*first;

	i = 0;
	first = ft_strdup("");
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE)
			sub = single_quote_expander(str, &i, ctx);
		else if (str[i] == DOUBLE_QUOTE)
			sub = double_quote_expander(str, &i, ctx);
		else
			sub = no_quote_expander(str, &i, ctx);
		ans = ft_strjoin(first, sub);
		free(first);
		free(sub);
		first = ans;
		i++;
	}
	return (first);
}

void	str_expander(char **str, t_context *ctx)
{
	char	*buf_str;
	char	*first;

	buf_str = *str;
	first = expand_concatenate(buf_str, ctx);
	free(buf_str);
	if (!ctx->include_quote && ft_strcmp(first, "") == 0)
	{
		free(first);
		first = NULL;
	}
	*str = first;
}

void	expand_environ(t_context *ctx)
{
	t_ast	*ast;

	if (ctx->sys_error)
		return ;
	ast = ctx->ast;
	env_var_expander(ast, ctx);
}

void	env_var_expander(t_ast *ast, t_context *ctx)
{
	t_token	*tmp;

	if (!ast)
		return ;
	env_var_expander(ast->right, ctx);
	env_var_expander(ast->left, ctx);
	tmp = ast->argv;
	while (tmp)
	{
		str_expander(&tmp->word, ctx);
		tmp = tmp->next;
	}
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q a.out");
// }
