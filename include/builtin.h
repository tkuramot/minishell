/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:55:48 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/24 11:09:32 by tkuramot         ###   ########.fr       */
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
t_env	*env_lst_node_new(char *new_env);
void	env_lst_add_back(t_env *lst, t_env *new);
void	env_lst_node_delete(t_env *lst, t_env *delete_node);
void	free_all_env_lst(t_env *lst);
size_t	env_lst_size(t_env *lst);
char *env_strjoin(char *name, char *value);

int	mini_echo(t_token *lst);
int	mini_exit(t_token *lst, t_env *env_lst);
int	mini_cd(t_token *token_lst, t_env *env_lst);
int	mini_handle_command(t_token *lst, t_env *env_lst);
int mini_env(const t_token *lst, t_env *env_lst);
int	mini_unset(const t_token *token_lst, t_env *env_lst);
int	mini_export(t_token *token_lst, t_env *env_lst);
int	mini_pwd(void);

t_env	*env_lst_init(void);
char	*get_environ_str(char *key, t_env *env_lst);

t_env	*decompress(char *env_name, t_env *env_lst);

#endif
