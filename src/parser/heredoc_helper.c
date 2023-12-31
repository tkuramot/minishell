/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:15:16 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 08:37:44 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "expander.h"
#include "utils.h"
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

static char	*heredoc_expander(char *str, size_t i, t_context *ctx)
{
	size_t	end;
	char	*left;
	char	*right;

	end = i;
	left = ft_strdup("");
	while (str[end])
	{
		if (str[end] == '$')
			right = expand_env_string(str, &end, ctx);
		else
			right = ft_substr(str, end, 1);
		if (!right)
		{
			free(left);
			return (NULL);
		}
		left = extend_str(left, right);
		if (!left)
			return (NULL);
		end++;
	}
	return (left);
}

char	*create_heredoc_file(void)
{
	char	*number;
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	while (i < INT_MAX)
	{
		number = ft_itoa(i);
		if (!number)
			return (NULL);
		if (name)
			free(name);
		name = ft_strjoin(HEREDOC, number);
		free(number);
		if (!name)
			return (NULL);
		if (access(name, F_OK | R_OK) == -1)
			return (name);
		i++;
	}
	return (NULL);
}

void	quote_handle_heredoc(int fd, char *end_of_file)
{
	pid_t	pid;
	char	*line;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		set_exec_child_sig_handler();
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, end_of_file) == 0)
			{
				free(line);
				break ;
			}
			ft_putendl_fd(line, fd);
			free(line);
		}
		close(fd);
		exit(0);
	}
	if (waitpid(pid, &status, 0) == -1)
		waitpid(pid, &status, 0);
}

static void	write_expanded(char *line, int fd, t_context *ctx)
{
	char	*expand;

	expand = heredoc_expander(line, 0, ctx);
	ft_putendl_fd(expand, fd);
	free(expand);
	free(line);
}

void	handle_heredoc(int fd, char *end_of_file, t_context *ctx)
{
	pid_t	pid;
	char	*line;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		set_heredoc_child_sig_handler();
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, end_of_file) == 0)
			{
				free(line);
				break ;
			}
			write_expanded(line, fd, ctx);
		}
		close(fd);
		exit(0);
	}
	if (waitpid(pid, &status, 0) == -1)
		waitpid(pid, &status, 0);
}

// int main(int argc, char **argv)
// {
// 	// int status;
// 	if(argc == 2){
// 		handle_heredoc(argv[1]);
// 	}
// 	// return (status);
// }

// int main(int argc, char **argv)
// {
// 	t_env *env_lst;

// 	env_lst = env_lst_init();
// 	if(argc == 2)
// 	{
// 		quote_handle_heredoc(argv[1], env_lst);
// 	}
// }
