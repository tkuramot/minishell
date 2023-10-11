/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:27:05 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 16:09:43 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	cd_no_such_file(char *command, char *file)
{
	ft_dprintf(1, "minishell: %s: ", command);
	perror(file);
}
