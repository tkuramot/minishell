/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:06:23 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/28 21:02:49 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "builtin.h"
#include "lexer.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
// #include "../../libft/include/libft.h"

void	ft_pwd(void);

char	*get_environ_str(char *key, char **environ)
{
	int		i;
	char	*value;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], key, ft_strlen(key)) == 0)
		{
			value = ft_strdup(ft_strchr(environ[i], '=') + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

// void mini_cd(char *str, char **environ){
// 	int directory;
// 	char	*path_env;

// 	path_env = get_environ_str("HOME=", environ);
// 	printf("%s\n", path_env);
// 	if(!str)
// 		directory = chdir(path_env);
// 	else{
// 		if (!access(str, X_OK))
// 			directory = chdir(str);
// 		else
// 			printf("どこ移動しようとしてんねん！\n");
// 	}
// 	if(directory)
// 		perror("cd");
// }

void mini_cd(t_token *lst, char **environ){
	int		directory = 0;
	char	*path_env;

	path_env = get_environ_str("HOME=", environ);
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
