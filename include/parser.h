/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:42 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/11 08:07:27 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "type.h"
# include <stdbool.h>

t_ast		*ast_new_node(t_node_type type, t_ast *left, t_ast *right);
t_ast		*ast_new_node_cmd(t_token *lst);
void		free_ast(t_ast *ast);
bool		expect(t_token *lst, t_token_type type);
bool		is_redirect(t_token *lst);
t_redirect	*init_redir(char *file, t_token_type type, t_context *ctx);
void		free_redir(void	*content);
t_ast		*arrange_node(t_context *ctx, t_ast *node);
void		parse_token(t_context *ctx);

#endif
