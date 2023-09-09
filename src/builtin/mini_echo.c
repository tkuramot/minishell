/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:35:18 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/09 18:22:55 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "builtin.h"

static bool	is_valid_option(char *option)
{
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
	ft_dprintf(STDOUT_FILENO, "%s ", lst->word);
		lst = lst->next;
	}
ft_dprintf(STDOUT_FILENO, "%s\n", lst->word);
	return (0);
}

int	mini_echo(t_token *lst)
{
	if (!lst)
	{
	ft_dprintf(STDOUT_FILENO, "\n");
		return (0);
	}
	if (is_valid_option(lst->word))
		return (echo_with_option_n(lst));
	return (echo_without_option_n(lst));
}
