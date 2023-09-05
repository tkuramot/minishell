/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:37:42 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/05 15:52:15 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static size_t	token_lst_size(const t_token *commond_lst)
{
	size_t	i;

	i = 0;
	while (commond_lst)
	{
		i++;
		commond_lst = commond_lst->next;
	}
	return (i);
}

char	**token_lst_to_array(const t_token *command_lst)
{
	size_t	i;
	size_t	command_lst_size;
	char	**command;

	command_lst_size = token_lst_size(command_lst);
	command = malloc(sizeof(char *) * (command_lst_size + 1));
	if (!command)
		return (NULL);
	i = 0;
	while (command_lst)
	{
		command[i] = ft_strdup(command_lst->word);
		if (!command[i])
			return (NULL);
		command_lst = command_lst->next;
		i++;
	}
	command[i] = NULL;
	return (command);
}
