/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:55:48 by tkuramot          #+#    #+#             */
/*   Updated: 2023/08/29 01:35:12 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
#include "lexer.h"


// 環境変数の線形リスト
typedef struct s_env	t_env;
struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
};

// env_lst_operations.c
t_env *env_lst_node_new(char *new_env);
void env_lst_add_back(t_env *lst, t_env *new);
void env_lst_node_delete(t_env *lst, t_env *delete_node);
t_env *env_lst_head(void);

int	mini_echo(int argc, char **argv);
void mini_exit(void);
void mini_cd(t_token *lst, char **environ);
void mini_handle_command(t_token *lst, t_env *env_lst);
void mini_env(const t_env *env_lst);
void mini_unset(const t_token *lst, t_env *env_lst);

t_env *env_lst_init(void);

t_env *decompress(t_token *lst, t_env *env_lst);

#endif
