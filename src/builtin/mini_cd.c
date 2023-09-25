/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:06:23 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/24 11:10:26 by tkuramot         ###   ########.fr       */
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

int	mini_cd(t_token *token_lst, t_env *env_lst)
{
	char	*path_env;
	char	*env_oldpwd;
	char	*env_pwd;

	env_oldpwd = get_pwd();
	if (!token_lst || !ft_strcmp(token_lst->word, "~"))
		path_env = get_environ_str("HOME", env_lst);
	else if (!ft_strncmp(token_lst->word, "~/", 2))
		path_env = ft_strjoin(get_environ_str("HOME", env_lst), \
												&token_lst->word[1]);
	else if (!ft_strcmp(token_lst->word, "-"))
		path_env = get_environ_str("OLDPWD", env_lst);
	else
		path_env = token_lst->word;
	if (chdir(path_env))
		perror("cd");
	else
	{
		update_env("OLDPWD", env_oldpwd, env_lst);
		env_pwd = get_pwd();
		update_env("PWD", env_pwd, env_lst);
		free(env_pwd);
	}
	free(env_oldpwd);
	return (0);
}

// int	mini_pwd(void)
// {
// ft_dprintf("%s\n", getenv("PWD"));
// 	return (0);
// }

// #include <stdio.h>
// int main(int argc, char **argv){
// 	extern char	**environ;
// 	mini_cd(argv[1], environ);
// 	// mini_pwd();
// 	ft_pwd();
// }
