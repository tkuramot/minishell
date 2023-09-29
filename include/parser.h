/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:19:42 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/29 12:52:34 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "type.h"

t_ast	*ast_new_node(t_node_type type, t_ast *left, t_ast *right);
t_ast	*ast_new_node_cmd(t_token *lst);
void	parse_token(t_context *ctx);

#endif
