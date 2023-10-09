/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:06:23 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/09 22:10:55 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*get_pwd(void)
{
	char	*pwd_path;

	pwd_path = ft_calloc(sizeof(char), PATH_MAX);
	if (!pwd_path)
		return (NULL);
	getcwd(pwd_path, PATH_MAX);
	if (!pwd_path)
		return (NULL);
	return (pwd_path);
}

static int	update_env(char *key, char *new_oldpwd, t_env *env_lst)
{
	char	*new_env_str;
	t_env	*new;
	t_env	*head;

	head = env_lst;
	while (env_lst)
	{
		if (ft_strcmp(key, env_lst->name) == 0)
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(new_oldpwd);
			if (!env_lst->value)
				return (0);
			return (1);
		}
		env_lst = env_lst->next;
	}
	new_env_str = env_strjoin(key, new_oldpwd);
	if (!new_env_str)
		return (0);
	new = env_lst_node_new(new_env_str);
	env_lst_add_back(head, new);
	free(new_env_str);
	return (1);
}

static char	*get_environ_str(char *key, t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strcmp(key, env_lst->name) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

static int	get_cd_path(t_token *token_lst, t_env *env_lst, char **path_env)
{
	char	*path;

	if (!token_lst)
	{
		path = get_environ_str("HOME", env_lst);
		if (!path)
		{
			ft_dprintf(1, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else if (!ft_strcmp(token_lst->word, "-"))
	{
		path = get_environ_str("OLDPWD", env_lst);
		if (!path)
		{
			ft_dprintf(1, "minishell: cd: OLDPWD not set\n");
			return (1);
		}
		ft_dprintf(1, "%s\n", path);
	}
	else
		path = token_lst->word;
	*path_env = path;
	return (0);
}

int	mini_cd(t_token *token_lst, t_env *env_lst)
{
	char	*path_env;
	char	*env_oldpwd;
	char	*env_pwd;

	path_env = NULL;
	env_oldpwd = get_pwd();
	if (get_cd_path(token_lst, env_lst, &path_env) == 1)
	{
		free(env_oldpwd);
		return (1);
	}
	if (chdir(path_env))
	{
		cd_no_such_file("cd", path_env);
		free(env_oldpwd);
		return (1);
	}
	update_env("OLDPWD", env_oldpwd, env_lst);
	env_pwd = get_pwd();
	update_env("PWD", env_pwd, env_lst);
	free(env_pwd);
	free(env_oldpwd);
	return (0);
}
