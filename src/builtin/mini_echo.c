/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:35:18 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/04 19:47:16 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "builtin.h"

static bool	is_valid_option(char *option)
{
	if (*option == '\0')
		return (false);
	if (ft_strncmp("-n", option, 2) == 0)
	{
		if (ft_strlen(option) <= 2)
			return (true);
		else
			option += 2;
	}
	while (*option && *option == 'n')
		option++;
	if (*option)
		return (false);
	return (true);
}

static int	echo_with_option_n(t_token *lst)
{
	while (lst && is_valid_option(lst->word))
		lst = lst->next;
	if (!lst)
		return (0);
	while (lst->next)
	{
		ft_dprintf(STDOUT_FILENO, "%s ", lst->word);
		lst = lst->next;
	}
	ft_dprintf(STDOUT_FILENO, "%s", lst->word);
	return (0);
}

static int	echo_without_option_n(t_token *lst)
{
	while (lst->next)
	{
		ft_dprintf(STDOUT_FILENO, "%s", lst->word);
		if(ft_strcmp(lst->word, "\0") != 0)
			ft_dprintf(STDOUT_FILENO, " ", lst->word);
		lst = lst->next;
	}
	ft_dprintf(STDOUT_FILENO, "%s\n", lst->word);
	return (0);
}

int	mini_echo(t_token *lst)
{
	if (!lst || (ft_strcmp(lst->word, "\0") == 0 && !lst->next))
	{
		ft_dprintf(STDOUT_FILENO, "\n");
		return (0);
	}
	if (is_valid_option(lst->word))
		return (echo_with_option_n(lst));
	return (echo_without_option_n(lst));
}
