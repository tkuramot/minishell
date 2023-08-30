/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:06:23 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/29 20:56:12 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
// #include "../../libft/include/libft.h"

void	ft_pwd(void);

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

// char	*get_environ_str(char *key, char **environ)
// {
// 	int		i;
// 	char	*value;

// 	i = 0;
// 	while (environ[i] != NULL)
// 	{
// 		if (ft_strncmp(environ[i], key, ft_strlen(key)) == 0)
// 		{
// 			value = ft_strdup(ft_strchr(environ[i], '=') + 1);
// 			return (value);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

void mini_cd(t_token *lst, t_env *env_lst)
{
	int		directory = 0;
	char	*path_env;

	path_env = get_environ_str("HOME", env_lst);
	printf("%s\n", path_env);
	if(!lst)
		directory = chdir(path_env);
	else if(!ft_strncmp(lst->word, "~", 1))
		printf("~ のみのときはHOMEと挙動一緒\n~/のときはHOMEにstrjoinかなあ\n先に展開つくるわ。");
	else if(!ft_strcmp(lst->word, "-"))
		printf("環境変数から一個前のパスを取ってくる予定。\n");
	else{
		if (!access(lst->word, X_OK))
			directory = chdir(lst->word);
		else
			printf("どこ移動しようとしてんねん！\n");
	}
	if(directory)
		perror("cd");
	ft_pwd();
}

// int	mini_pwd(void)
// {
// 	printf("%s\n", getenv("PWD"));
// 	return (0);
// }

void	ft_pwd(void)
{
	char	*path_name;

	path_name = calloc(PATH_MAX, sizeof(char));
	if (path_name == NULL)
		return ;
	getcwd(path_name, PATH_MAX);
	if (path_name == NULL) ;
		// ft_puterr(strerror(errno));
	else
		printf("%s\n", path_name);
	free(path_name);
}

// #include <stdio.h>
// int main(int argc, char **argv){
// 	extern char	**environ;
// 	mini_cd(argv[1], environ);
// 	// mini_pwd();
// 	ft_pwd();
// }
