/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:35:18 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/20 17:18:02 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(argv[1], "-n", 2) == 0)
		;
	return (EXIT_SUCCESS);
}
