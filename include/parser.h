/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:42 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/18 22:58:21 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lexer.h"

typedef enum e_node_type
{
	ND_CMD,
	ND_PIPE
} t_node_type;

typedef struct s_ast t_ast;
struct s_ast
{
	t_node_type	type;
	t_token		*argv;
	t_list		*red_in;
	t_list		*red_out;
	t_list		*red_heredoc;
	t_list		*red_append;
	t_ast		*left;
	t_ast		*right;
	t_token		*lst;
};

t_ast	*ast_new_node(t_node_type type, t_ast *left, t_ast *right);
t_ast	*ast_new_node_cmd(t_token *lst);
t_ast	*parse_token(t_token *lst);

#endif
