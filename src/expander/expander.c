/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:42:36 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/23 21:10:29 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "parser.h"
#include "libft.h"
#include <libc.h>
// #include "../../libft/include/libft.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

char	*single_quote_expander(char *str, size_t *i)
{
	char	*ans;
	size_t	j;

	j = *i;
	while (str[j] != SINGLE_QUOTE)
		j++;
	ans = ft_substr(str, *i, j - *i);
	if (!ans)
		return (NULL);
	*i = j;
	return (ans);
}

// char	*double_quote_expander(char *str, size_t *i)
// {
// 	char	*ans;
// 	size_t	j;

// 	j = *i + 1;
// 	while (str[j] != DOUBLE_QUOTE)
// 		j++;
// 	ans = ft_substr(str, *i + 1, j - (*i + 1));
// 	if (!ans)
// 		return (NULL);
// 	*i = j;
// 	return (ans);
// }

char	*double_quote_expander(char *str, size_t *i)
{
	char	*ans;
	size_t	j;

	j = *i + 1;
	while (str[j] != DOUBLE_QUOTE)
		j++;
	ans = ft_substr(str, *i + 1, j - (*i + 1));
	if (!ans)
		return (NULL);
	*i = j;
	return (ans);
}

char	*no_quote_expander(char *str, size_t *i)
{
	char *ans;
	size_t	j;

	j = *i;
	while(str[j] != DOUBLE_QUOTE && str[j] != SINGLE_QUOTE && str[j] != '\0')
		j++;
	// dprintf(1, "AAA %zu = %zu\n", *i, j - *i);
	ans = ft_substr(str, *i, j - *i);
	if (!ans)
		return (NULL);
	*i = j - 1;
	return (ans);
}

void	str_expander(char **str)
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
			sub = double_quote_expander(*str, &i);
		else
			sub = no_quote_expander(*str, &i);
		ans = ft_strjoin(first, sub);
		free(first);
		free(sub);
		first = ans;
		i++;
	}
	// free(*str);
	*str = first;
}

void name(t_ast *ast)
{
	t_token *tmp;

	tmp = ast->argv;
	while(tmp)
	{
		str_expander(&tmp->word);
		tmp = tmp->next;
	}
}

// int main(void)
// {
// 	char *str = ft_strdup("012");
// 	printf("before == %s\n", str);
// 	str_expander(&str);
// 	printf("after  == %s\n", str);
// 	free(str);
// }

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q a.out");
// }
