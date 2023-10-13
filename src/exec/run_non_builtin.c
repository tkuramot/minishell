/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_non_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:26:03 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/13 00:41:30 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

static char	*get_env_value(char *key, char **environ)
{
	size_t	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], key, ft_strlen(key)) == 0)
			return (ft_substr(ft_strchr(environ[i], '='),
					1, ft_strlen(environ[i])));
		i++;
	}
	return (NULL);
}

int	get_path_type(char *cmd)
{
	size_t	i;

	i = 0;
	if (cmd[i] == '/')
		return (1);
	i++;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	run_non_builtin_helper(char **cmd, char **environ)
{
	char	*cmd_full_path;
	char	*path_env;

	set_exec_child_sig_handler();
	path_env = get_env_value("PATH", environ);
	cmd_full_path = resolve_path(cmd[0], path_env);
	if (get_path_type(cmd[0]))
	{
		if (!is_executable(cmd[0]))
			perror_exit(cmd[0], 127);
		if (!is_directory(cmd[0]))
			perror_exit(cmd[0], 126);
		if (execve(cmd[0], cmd, environ) == -1)
			cmd_not_found_error(cmd[0]);
	}
	if (execve(cmd_full_path, cmd, environ) == -1)
		cmd_not_found_error(cmd[0]);
}

int	run_non_builtin_child(t_token *lst, t_env *env_lst)
{
	pid_t	pid;
	int		status;
	char	**cmd;
	char	**env;

	cmd = token_lst_to_array(lst);
	env = env_list_to_array(env_lst);
	pid = fork();
	if (pid == 0)
		run_non_builtin_helper(cmd, env);
	waitpid(pid, &status, 0);
	free_two_d_array(env);
	free_two_d_array(cmd);
	return (WEXITSTATUS(status));
}

void	run_non_builtin_parent(t_token *lst, t_env *env_lst)
{
	char	**cmd;
	char	**env;

	cmd = token_lst_to_array(lst);
	env = env_list_to_array(env_lst);
	run_non_builtin_helper(cmd, env);
}
