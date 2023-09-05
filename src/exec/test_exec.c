/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:15:00 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/04 16:36:25 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**get_environ_str1(char *key, char **environ)
{
	int		i;
	char	**value;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], key, ft_strlen(key)) == 0)
		{
			value = ft_split(environ[i], '=');
			return (value);
		}
		i++;
	}
	return (NULL);
}

char	**split_command(char *unformatted_command)
{
	char	**command;

	command = ft_split(unformatted_command, ' ');
	return (command);
}

char	*resolve_path(char *command, char *path_env)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, command);
		free(path);
		// printf("%d ==== %s\n", i, full_path);
		if (is_executable(full_path))
		{
			// free_two_d_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	// free_two_d_array(paths);
	return (NULL);
}

void	handle_command(char *raw_command, char **environ)
{
	char	**command;
	char	*command_full_path;
	char	**path_env;

	command = split_command(raw_command);
	// if (is_readable(command[0]) == -1)
	//  if (is_executable(command[0]))
	//  {
	// 	if(execve(command[0], command, environ) == -1)
	// 		perror("execve");
	// 	// exit_free_perror(command, NULL);
	// 	// printf("これ見える\n");
	// 	exit(0);
	//  }
	path_env = get_environ_str1("PATH", environ);
	command_full_path = resolve_path(command[0], path_env[1]);
	// free_two_d_array(path_env);
	// if (command_full_path == NULL)
	// 	exit_free_strerror("command not found", command[0], command, NULL);
	execve(command_full_path, command, environ);
	// exit_free_perror(command, command_full_path);
	if (is_executable(command[0]))
	 {
		if(execve(command[0], command, environ) == -1)
			perror("execve");
		// exit_free_perror(command, NULL);
		// printf("これ見える\n");
		exit(0);
	 }
}

int	test_exec(char *path, char **env)
{
	pid_t	pid;
	int status;

	pid = fork();
	if (pid == 0)
		handle_command(path, env);
		// execve("/bin/ls", cmd1, environ);
	waitpid(pid, &status, 0);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	pid_t	pid;
// 	int status;
// 	extern char	**environ;

// 	pid = fork();
// 	if (pid == 0)
// 		handle_command(argv[1], environ);
// 		// execve("/bin/ls", cmd1, environ);
// 	waitpid(pid, &status, 0);
// 	printf("aaa");
// 	return (0);
// }
