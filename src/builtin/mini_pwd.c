/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:23:23 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/28 11:22:50 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

int	mini_pwd(void)
{
	printf("%s\n", getenv("PWD"));
	return (0);
}
