/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:06:23 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/31 00:02:28 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int	update_path(char *env_name, char *path, t_env *env_lst)
{
	printf("PATHPATH==============%s\n", path);
	while(env_lst)
	{
		if(ft_strcmp(env_name, env_lst->name) == 0)
		{
			free(env_lst->value);
			env_lst->value = ft_strdup(path);
			if(env_lst->value == NULL)
				return(0);
			return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

char	*get_environ_str(char *key, t_env *env_lst)
{
	while(env_lst)
	{
		if(ft_strcmp(key, env_lst->name) == 0)
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void mini_cd(t_token *lst, t_env *env_lst)
{
	int		directory = 0;
	char	*path_env;

	path_env = NULL;
	if(!lst || !ft_strcmp(lst->word, "~")){
		path_env = get_environ_str("HOME", env_lst);
		directory = chdir(path_env);
	}
	else if(!ft_strncmp(lst->word, "~", 1))
		printf("~ のみのときはHOMEと挙動一緒\n~/のときはHOMEにstrjoinかなあ\n先に展開つくるわ。");
	else if(!ft_strcmp(lst->word, "-")){
		path_env = get_environ_str("OLDPWD", env_lst);
		directory = chdir(path_env);
	}
	else{
		path_env = lst->word;
		directory = chdir(path_env);
	}
	if(directory)
		perror("cd");
	printf("OLDPATH=================%s\n", path_env);
	update_path("OLDPWD", path_env, env_lst);
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
