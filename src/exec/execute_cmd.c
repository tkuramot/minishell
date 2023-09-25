/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:26:03 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/25 11:51:46 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_env_value(char *key, char **environ)
{
	size_t	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], key, ft_strlen(key)) == 0)
			return (ft_substr(ft_strchr(environ[i], '='),
					0, ft_strlen(environ[i])));
		i++;
	}
	return (NULL);
}

static void	execve_cmd(char **cmd, char **environ)
{
	char	*cmd_full_path;
	char	*path_env;

	path_env = get_env_value("PATH", environ);
	cmd_full_path = resolve_path(cmd[0], path_env);
	if (strncmp("./", cmd[0], 2) == 0)
	{
		execve(cmd[0], cmd, environ);
		exit(0);
	}
	execve(cmd_full_path, cmd, environ);
	if (is_executable(cmd[0]))
	{
		if (execve(cmd[0], cmd, environ) == -1)
			perror("execve");
		exit(0);
	}
	exit(0);
}

int	run_cmd_child(t_token *lst, t_env *env_lst)
{
	pid_t	pid;
	int		status;
	char	**cmd;
	char	**env;

	cmd = token_lst_to_array(lst);
	env = env_list_to_array(env_lst);
	pid = fork();
	if (pid == 0)
		execve_cmd(cmd, env);
	waitpid(pid, &status, 0);
	free_two_d_array(env);
	free_two_d_array(cmd);
	return (status);
}

void	run_cmd_parent(t_token *lst, t_env *env_lst)
{
	char	**cmd;
	char	**env;

	cmd = token_lst_to_array(lst);
	env = env_list_to_array(env_lst);
	execve_cmd(cmd, env);
}
