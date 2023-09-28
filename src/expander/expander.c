/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:42:36 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/29 01:41:44 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"
#include <libc.h>

void	str_expander(char **str, t_env *env_lst)
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
			sub = double_quote_expander(*str, &i, env_lst);
		else
			sub = no_quote_expander(*str, &i, env_lst);
		ans = ft_strjoin(first, sub);
		free(first);
		free(sub);
		first = ans;
		i++;
	}
	// free(*str);
	*str = first;
}

void env_var_expander(t_ast *ast, t_env *env_lst)
{
	t_token *tmp;

	tmp = ast->argv;
	while(tmp)
	{
		str_expander(&tmp->word, env_lst);
		tmp = tmp->next;
	}
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q a.out");
// }
