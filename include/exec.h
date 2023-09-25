/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:14:10 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/24 12:24:29 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define PIPE_READ 0
# define PIPE_WRITE 1

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
# include "libft.h"
# include "builtin.h"
# include "parser.h"

int		execute(t_ast *ast, t_env *env_lst);
int		run_simple_cmd(t_token *token_lst, t_env *env_lst);
int		run_simple_cmd_child(t_token *token_lst, t_env *env_lst);
int		run_cmd_child(t_token *token_lst, t_env *env_lst);
void	run_cmd_parent(t_token *lst, t_env *env_lst);
void	run_cmd(char **command, char **environ);
char	*resolve_path(char *cmd, char *path_env);
int		is_executable(char *command);
int		is_readable(char *command);
char	**env_list_to_array(t_env *env_lst);
void	free_two_d_array(char **array);

char **token_lst_to_array(const t_token *command_lst);


#endif
