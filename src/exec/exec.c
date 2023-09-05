/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:26:03 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/05 15:56:02 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// char	**get_environ_str1(char *key, char **environ)
// {
// 	int		i;
// 	char	**value;

// 	i = 0;
// 	while (environ[i] != NULL)
// 	{
// 		if (ft_strncmp(environ[i], key, ft_strlen(key)) == 0)
// 		{
// 			value = ft_split(environ[i], '=');
// 			return (value);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*resolve_path(char *command, char *path_env)
// {
// 	char	**paths;
// 	char	*path;
// 	char	*full_path;
// 	int		i;

// 	paths = ft_split(path_env, ':');
// 	i = 0;
// 	while (paths[i] != NULL)
// 	{
// 		path = ft_strjoin(paths[i], "/");
// 		full_path = ft_strjoin(path, command);
// 		free(path);
// 		if (is_executable(full_path))
// 			return (full_path);
// 		free(full_path);
// 		i++;
// 	}
// 	return (NULL);
// }

// void	handle_command(char *raw_command, char **environ)
// {
// 	char	**command;
// 	char	*command_full_path;
// 	char	**path_env;

// 	command = ft_split(raw_command, ' ');
// 	path_env = get_environ_str1("PATH", environ);
// 	command_full_path = resolve_path(command[0], path_env[1]);
// 	execve(command_full_path, command, environ);
// 	if (is_executable(command[0]))
// 	{
// 		if (execve(command[0], command, environ) == -1)
// 			perror("execve");
// 		exit(0);
// 	}
// 	exit(0);
// }

// int	exec(char *path, char **env)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == 0)
// 		handle_command(path, env);
// 	waitpid(pid, &status, 0);
// 	return (0);
// }


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
		if (is_executable(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	handle_command(char **command, char **environ)
{
	char	*command_full_path;
	char	**path_env;

	path_env = get_environ_str1("PATH", environ);
	command_full_path = resolve_path(command[0], path_env[1]);
	execve(command_full_path, command, environ);
	if (is_executable(command[0]))
	{
		if (execve(command[0], command, environ) == -1)
			perror("execve");
		exit(0);
	}
	exit(0);
}

int	exec(char **command, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		handle_command(command, env);
	waitpid(pid, &status, 0);
	return (0);
}