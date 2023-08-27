/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:59:15 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/27 06:49:09 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

void	fatal_error(char *err)
{
	ft_dprintf(STDERR_FILENO, "%s\n", err);
	exit(1);
}
