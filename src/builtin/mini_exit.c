/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:10:58 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/09 22:26:52 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "builtin.h"

// static bool	is_numeric(char *str)
// {
// 	size_t i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if(!ft_isdigit(str[i]))
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

int	mini_exit(t_token *lst, t_env *env_lst)
{
	token_lst_free(lst);
	free_all_env_lst(env_lst);
	if (!lst->next)
		exit(0);
	// else
	// {
	// 	// if(is_numeric(lst->next->word));
	// }
	return (0);
}

// exit(status)みたいな形で終了すべき？
// exit内でfreeする関数多そう
