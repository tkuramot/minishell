/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_handle_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:22:12 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/14 13:28:25 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "lexer.h"
#include "exec.h"

void mini_handle_command(t_token *lst, t_env *env_lst)
{
	t_env *buf;
	extern char	**environ;

	if (ft_strcmp(lst->word, "exit") == 0){
		mini_exit(lst, env_lst);
	}
	else if (ft_strcmp(lst->word, "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(lst->word, "cd") == 0)
		mini_cd(lst->next, env_lst);
	else if (ft_strcmp(lst->word, "env") == 0)
		mini_env(lst->next, env_lst);
	else if (ft_strcmp(lst->word, "unset") == 0)
		mini_unset(lst->next, env_lst);
	else if (ft_strcmp(lst->word, "export") == 0)
		mini_export(lst->next, env_lst);
	else if (ft_strcmp(lst->word, "echo") == 0)
		mini_echo(lst->next);
	else if (ft_strncmp(lst->word, "$", 1) == 0)
	{
		buf = decompress(lst->word, env_lst);
		if(!buf){
		ft_dprintf(STDOUT_FILENO, "そんな環境変数ねーだろ。\n");
			return ;
		}
	ft_dprintf(STDOUT_FILENO, "%s\n", buf->value);
	} else
		exec(lst, env_lst);
}
