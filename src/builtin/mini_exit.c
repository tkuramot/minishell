/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:10:58 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/12 23:08:16 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#define LONG_MIN_STRLEN 20

static bool	is_overflow(char *str)
{
	size_t	len;
	size_t	num;
	int		flag;

	len = ft_strlen(str);
	if (len > LONG_MIN_STRLEN)
		return (false);
	num = 0;
	flag = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	if ((num > LONG_MAX && flag == 1) || (num - 1 > LONG_MAX && flag == -1))
		return (false);
	return (true);
}

static bool	is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

int	mini_exit(t_token *lst, t_env *env_lst, bool is_parent)
{
	if (is_parent)
		ft_dprintf(STDERR_FILENO, "exit\n");
	if (!lst)
		exit(0);
	else
	{
		if (!is_numeric(lst->word) || !is_overflow(lst->word))
		{
			numeric_error(lst->word);
			token_lst_free(lst);
			free_all_env_lst(env_lst);
			exit(255);
		}
		if (lst->next)
		{
			too_many_error();
			return (1);
		}
		free_all_env_lst(env_lst);
		exit (ft_atoi(lst->word) % 256);
	}
	return (0);
}
