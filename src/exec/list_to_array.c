/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:30:33 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/05 16:09:25 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtin.h"

char	**env_list_to_array(t_env *env_lst)
{
	size_t	i;
	size_t	lst_size;
	char	**env_array;
	char	*buf;

	i = 0;
	lst_size = env_lst_size(env_lst);
	env_array = malloc(sizeof(char *) * (lst_size + 1));
	if (!env_array)
		return (NULL);
	while (env_lst)
	{
		buf = ft_strjoin(env_lst->name, "=");
		if (!buf)
			return (NULL);
		env_array[i] = ft_strjoin(buf, env_lst->value);
		if (!env_array[i])
			return (NULL);
		free(buf);
		env_lst = env_lst->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

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

void	free_two_d_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
