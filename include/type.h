/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:17:36 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/14 22:21:34 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include "libft.h"
# include <stdbool.h>

typedef enum e_token_type
{
	TK_REDIR_IN = 0,
	TK_REDIR_OUT = 1,
	TK_REDIR_APPEND = 2,
	TK_REDIR_HEREDOC = 3,
	TK_WORD,
	TK_PIPE,
	TK_EOF,
}	t_token_type;

typedef struct s_token	t_token;
struct s_token
{
	char			*word;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
};

typedef enum e_node_type
{
	ND_CMD,
	ND_PIPE
}	t_node_type;

typedef struct s_redirect
{
	char			*file;
	t_token_type	type;
}	t_redirect;

typedef struct s_ast	t_ast;
struct s_ast
{
	t_node_type	type;
	t_token		*argv;
	t_list		*redir_lst;
	t_ast		*left;
	t_ast		*right;
	t_token		*lst;
};

typedef struct s_env	t_env;
struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
};

typedef struct s_context
{
	t_token	*token;
	t_ast	*ast;
	t_env	*env;
	int		status;
	bool	sys_error;
	bool	include_quote;
}	t_context;

#endif
