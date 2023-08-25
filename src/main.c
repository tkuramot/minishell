/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:33:13 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/25 15:45:46 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int	main(void)
{
	char	*line;

	while (true)
	{
		line = readline("\x1b[32mminishell$ \x1b[0m");
		if (!line)
			return (1);
		if (*line)
			add_history(line);
		// parse line
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
