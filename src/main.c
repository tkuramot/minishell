/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:33:13 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/24 18:02:42 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int	main(void)
{
	char	*line;

	line = readline("\x1b[32mminishell$ \x1b[0m");
	while (line)
	{
		// parse line
		printf("%s\n", line);
		if (line && *line)
			add_history(line);
		free(line);
		line = readline("\x1b[32mminishell$ \x1b[0m");
	}
	return (0);
}
