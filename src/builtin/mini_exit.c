/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:10:58 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/12 02:05:18 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

static void	numeric_error(char *status)
{
	ft_dprintf(STDERR_FILENO, "minishell: exit: ");
	ft_dprintf(STDERR_FILENO, "%s: ", status);
	ft_dprintf(STDERR_FILENO, "numeric argument required\n");
}

static void	too_many_error(void)
{
	ft_dprintf(STDERR_FILENO, "minishell: exit: ");
	ft_dprintf(STDERR_FILENO, "too many arguments\n");
}

int	mini_exit(t_token *lst, t_env *env_lst)
{
	if (!lst)
		exit(0);
	else
	{
		if (!is_numeric(lst->word))
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
