/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:35:18 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/09 12:30:22 by tsishika         ###   ########.fr       */
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
		printf("%s ", lst->word);
		lst = lst->next;
	}
	printf("%s", lst->word);
	return (0);
}

static int	echo_without_option_n(t_token *lst)
{
	while (lst->next)
	{
		printf("%s ", lst->word);
		lst = lst->next;
	}
	printf("%s\n", lst->word);
	return (0);
}

int	mini_echo(t_token *lst)
{
	if (!lst)
	{
		printf("\n");
		return (0);
	}
	if (is_valid_option(lst->word))
		return (echo_with_option_n(lst));
	return (echo_without_option_n(lst));
}
