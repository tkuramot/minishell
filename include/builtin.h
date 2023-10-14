/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:55:48 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/14 16:20:09 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "lexer.h"
# include "utils.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>

extern char	**environ;

# define LONG_MIN_STRLEN 20
# define FIND_FILE 2

t_env	*env_lst_node_new(char *new_env);
void	env_lst_add_back(t_env *lst, t_env *new);
void	env_lst_node_delete(t_env *lst, t_env *delete_node);
void	free_all_env_lst(t_env *lst);
size_t	env_lst_size(t_env *lst);
char	*env_strjoin(char *name, char *value);
int		mini_echo(t_token *lst);
int		mini_exit(t_token *lst, t_env *env_lst, bool is_parent);
int		mini_cd(t_token *token_lst, t_env *env_lst);
int		mini_export(t_token *token, t_env *env);
int		mini_env(const t_token *lst, t_env *env_lst);
int		mini_unset(const t_token *token_lst, t_env *env_lst);
int		mini_export(t_token *token_lst, t_env *env_lst);
int		mini_pwd(void);
void	env_init(t_context *ctx);
void	cd_no_such_file(char *command, char *file);
t_env	*env_lst_head(void);
void	export_not_a_valid(char *str);

#endif
