/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:23:23 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/24 11:10:39 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "builtin.h"

int	mini_pwd(void)
{
	char	pwd_path[PATH_MAX];

	if (!getcwd(pwd_path, PATH_MAX))
		perror("pwd");
	else
		ft_dprintf(STDOUT_FILENO, "%s\n", pwd_path);
	return (0);
}
