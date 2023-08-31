/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_handle_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:22:12 by tsishika          #+#    #+#             */
/*   Updated: 2023/08/31 13:43:37 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"

// 条件式が長すぎ。strncmpだと"exito" とかが弾けない。strcmp作るべきだろうなあって感じ。
// mini_echoの引数が現状だとどう扱っていいかわからない。私的にはchar **strで受け取っておいてあげたいがどうしよっかなあって感じ。
// lstごともらって内部で次の文字調べてもいいけどこのへんは構文解析でなんとかできるのでは。わかんねえ
// 現状はexitできるようにしたからこのまま放置

void mini_handle_command(t_token *lst, t_env *env_lst)
{
	t_env *buf;
	extern char	**environ;

	if (ft_strcmp(lst->word, "exit") == 0)
		mini_exit();
	if (ft_strcmp(lst->word, "pwd") == 0)
		mini_pwd();
	if (ft_strcmp(lst->word, "cd") == 0)
		mini_cd(lst->next, env_lst);
	if (ft_strcmp(lst->word, "env") == 0)
		mini_env(env_lst);
	if (ft_strcmp(lst->word, "unset") == 0)
		mini_unset(lst->next, env_lst);
	if (ft_strcmp(lst->word, "export") == 0)
		mini_export(lst->next->word, env_lst);
	if (ft_strncmp(lst->word, "$", 1) == 0)
	{
		buf = decompress(lst->word, env_lst);
		if(!buf){
			printf("そんな環境変数ねーだろ。\n");
			return ;
		}
		printf("%s\n", buf->value);
	}
}
