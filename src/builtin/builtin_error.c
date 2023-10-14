/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:27:05 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/14 16:19:54 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	cd_no_such_file(char *command, char *file)
{
	ft_dprintf(1, "minishell: %s: ", command);
	perror(file);
}

void	export_not_a_valid(char *str)
{
	ft_dprintf(1, "minishell: export: %s: ", str);
	ft_dprintf(1, "not a valid identifier\n");
}
