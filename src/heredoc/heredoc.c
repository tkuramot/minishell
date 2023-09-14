/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:15:16 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/09 12:45:19 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
// #include "libc.h"
#include <readline/readline.h>
#include <readline/history.h>

void handle_heredoc(char *end_of_file)
{
	pid_t	pid;
	char *line;
	int fd;
	int status;

	pid = fork();
	if(pid == 0)
	{
		fd = open("HEREDOC", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		while(1)
		{
			line = readline(">");
			if(ft_strcmp(line, end_of_file) == 0)
			{
				free(line);
				break;
			}
			ft_putendl_fd(line, fd);
			free(line);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	waitpid(pid, &status, 0);
	exit(0);
}

// int main(int argc, char **argv)
// {
// 	// int status;
// 	if(argc == 2){
// 		handle_heredoc(argv[1]);
// 	}
// 	// return (status);
// }
