/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:42:36 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/24 19:11:23 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "parser.h"
#include "exec.h"
#include "libft.h"
#include <libc.h>
// #include "../../libft/include/libft.h"

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

char	*get_env_value(char *str, size_t *i, t_env *env_lst)
{
	size_t	j;
	char	*serch_name;
	char	*get_env_value;

	j = *i + 1;
	if (str[j] == '$' || str[j] == '\0')
	{
		get_env_value = ft_strdup("$");
		return (get_env_value);
	}
	while (str[j] && str[j] != '$')
		j++;
	serch_name = ft_substr(str, *i + 1, j - (*i + 1));
	if (!serch_name)
		exit(1);
	while (env_lst)
	{
		if (ft_strcmp(serch_name, env_lst->name) == 0)
		{
			get_env_value = ft_strdup(env_lst->value);
			if (!get_env_value)
				exit(0);
			break ;
		}
		env_lst = env_lst->next;
	}
	if (!env_lst)
		get_env_value = ft_strdup("");
	*i = j - 1;
	free(serch_name);
	return (get_env_value);
}

char	*get_env_value1(char *str, size_t *i, t_env *env_lst)
{
	size_t	j;
	char	*serch_name;
	char	*get_env_value;

	j = *i + 1;
	if (str[j] == '$' || str[j] == '\0')
	{
		get_env_value = ft_strdup("$");
		return (get_env_value);
	}
	while (str[j] != DOUBLE_QUOTE && str[j] != '$')
		j++;
	serch_name = ft_substr(str, *i + 1, j - (*i + 1));
	if (!serch_name)
		exit(1);
	while (env_lst)
	{
		if (ft_strcmp(serch_name, env_lst->name) == 0)
		{
			get_env_value = ft_strdup(env_lst->value);
			if (!get_env_value)
				exit(0);
			break ;
		}
		env_lst = env_lst->next;
	}
	if (!env_lst)
		get_env_value = ft_strdup("");
	*i = j - 1;
	free(serch_name);
	return (get_env_value);
}

char	*single_quote_expander(char *str, size_t *i)
{
	char	*ans;
	size_t	j;

	j = *i + 1;
	while (str[j] != SINGLE_QUOTE)
		j++;
	ans = ft_substr(str, *i + 1, j - (*i + 1));
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

char	*double_quote_expander(char *str, size_t *i, t_env *env_lst)
{
	char	*sub;
	char	*first;
	char	*ans;
	size_t	j;

	j = *i + 1;
	first = ft_strdup("");
	while(str[j] != DOUBLE_QUOTE && str[j] != '\0')
	{
		if(str[j] == '$')
			sub = get_env_value1(str, &j, env_lst);
		else
			sub = ft_substr(str, j, 1);
		ans = ft_strjoin(first, sub);
		free(first);
		free(sub);
		first = ans;
		j++;
	}
	*i = j;
	return (first);
}

char	*no_quote_expander(char *str, size_t *i, t_env *env_lst)
{
	char	*sub;
	char	*first;
	char	*ans;
	size_t	j;

	j = *i;
	first = ft_strdup("");
	while(str[j] != DOUBLE_QUOTE && str[j] != SINGLE_QUOTE && str[j] != '\0')
	{
		if(str[j] == '$')
			sub = get_env_value(str, &j, env_lst);
		else
		{
			sub = ft_substr(str, j, 1);
			ft_dprintf(1, "B\n");
		}
		ans = ft_strjoin(first, sub);
		free(first);
		free(sub);
		first = ans;
		j++;
	}
	*i = j - 1;
	return (first);
}

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
