/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:06:23 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/02 23:35:34 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

// bash起動後すぐに "cd -" を実行した際、"cd: Bad address" ではなく、"cd: OLDPWD not set"にするひつようがあるかも

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

// static int	update_oldpwd(char *new_oldpwd, t_env *env_lst)
// {
// 	while (env_lst)
// 	{
// 		if (ft_strcmp("OLDPWD", env_lst->name) == 0)
// 		{
// 			free(env_lst->value);
// 			env_lst->value = ft_strdup(new_oldpwd);
// 			if (!env_lst->value)
// 				return (0);
// 			return (1);
// 		}
// 		env_lst = env_lst->next;
// 	}
// 	return (0);
// }

static int	update_oldpwd(char *new_oldpwd, t_env *env_lst)
{
	char	*new_oldpwd_str;
	t_env	*new;
	t_env	*head;

	head = env_lst;
	while (env_lst)
	{
		if (ft_strcmp("OLDPWD", env_lst->name) == 0)
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(new_oldpwd);
			if (!env_lst->value)
				return (0);
			return (1);
		}
		env_lst = env_lst->next;
	}
	new_oldpwd_str = ft_strjoin("OLDPWD=", new_oldpwd);
	new = env_lst_node_new(new_oldpwd_str);
	env_lst_add_back(head, new);
	free(new_oldpwd_str);
	return (0);
}

char	*get_environ_str(char *key, t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strcmp(key, env_lst->name) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	mini_cd(char *path, t_env *env_lst)
{
	int		directory;
	char	*path_env;
	char	*new_oldpwd;

	directory = 0;
	path_env = NULL;
	new_oldpwd = get_pwd();
	if (!path || !ft_strcmp(path, "~"))
		path_env = get_environ_str("HOME", env_lst);
	else if (!ft_strncmp(path, "~/", 2))
		path_env = ft_strjoin(get_environ_str("HOME", env_lst), &path[1]);
	else if (!ft_strcmp(path, "-"))
		path_env = get_environ_str("OLDPWD", env_lst);
	else
		path_env = path;
	directory = chdir(path_env);
	if (directory)
		perror("cd");
	else
		update_oldpwd(new_oldpwd, env_lst);
	free(new_oldpwd);
}

// int	mini_pwd(void)
// {
// 	printf("%s\n", getenv("PWD"));
// 	return (0);
// }

// #include <stdio.h>
// int main(int argc, char **argv){
// 	extern char	**environ;
// 	mini_cd(argv[1], environ);
// 	// mini_pwd();
// 	ft_pwd();
// }
