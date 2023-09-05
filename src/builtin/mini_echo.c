/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:35:18 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/06 01:09:48 by tsishika         ###   ########.fr       */
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

// static int	echo_with_option_n(int argc, char **argv)
// {
// 	int64_t	i;

// 	i = 1;
// 	while (i < argc && is_valid_option(argv[i]))
// 		i++;
// 	while (i < argc)
// 	{
// 		ft_putstr_fd(argv[i], STDOUT_FILENO);
// 		if (i < argc - 1)
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 		i++;
// 	}
// 	return (0);
// }

// static int	echo_without_option_n(int argc, char **argv)
// {
// 	int64_t	i;

// 	i = 1;
// 	while (i < argc)
// 	{
// 		ft_putstr_fd(argv[i], STDOUT_FILENO);
// 		if (i < argc - 1)
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 		i++;
// 	}
// 	ft_putstr_fd("\n", STDOUT_FILENO);
// 	return (0);
// }

// int	mini_echo(int argc, char **argv)
// {
// 	if (argc == 1)
// 	{
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 		return (0);
// 	}
// 	if (is_valid_option(argv[1]))
// 		return (echo_with_option_n(argc, argv));
// 	return (echo_without_option_n(argc, argv));
// }

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
