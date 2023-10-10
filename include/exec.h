/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:14:10 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 02:30:24 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define PIPE_READ 0
# define PIPE_WRITE 1
# define IS_A_DIRECTORY 21

# include "builtin.h"
# include "libft.h"
# include "parser.h"
# include "redirect.h"
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>

void	execute(t_context *ctx);
// int		run_simple_cmd(t_token *token_lst, t_env *env_lst);
int	run_simple_cmd(t_token **token_lst, t_env *env_lst);
void	run_simple_cmd_parent(t_token *token_lst, t_env *env_lst);
void	run_non_builtin_parent(t_token *lst, t_env *env_lst);
int		run_non_builtin_child(t_token *lst, t_env *env_lst);
char	*resolve_path(char *cmd, char *path_env);
int		is_executable(char *command);
int		is_readable(char *command);
int		is_directory(char *command);
char	**env_list_to_array(t_env *env_lst);
void	free_two_d_array(char **array);
char	**token_lst_to_array(const t_token *command_lst);

#endif
