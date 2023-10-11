/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:18:08 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/11 15:04:41 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "type.h"
#include "utils.h"
#include <stdlib.h>

void	free_cmd_related_malloc(t_context *ctx, char **line)
{
	free(*line);
	*line = NULL;
	if (!ctx)
		return ;
	free_ast(ctx->ast);
	ctx->ast = NULL;
	token_lst_free(ctx->token);
	ctx->token = NULL;
}
