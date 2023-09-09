/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:23:23 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/06 01:10:34 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "builtin.h"

void	mini_pwd(void)
{
	char	pwd_path[PATH_MAX];

	if (!getcwd(pwd_path, PATH_MAX))
		perror("pwd");
	else
		printf("%s\n", pwd_path);
}
