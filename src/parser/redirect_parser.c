/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:12:17 by tkuramot          #+#    #+#             */
/*   Updated: 2023/10/10 02:06:56 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"
#include "libft.h"

int is_space(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

bool	is_whitespace(char *file)
{
	size_t	i;

	i = 0;
	while(file[i])
	{
		if(is_space(file[i]))
			return (false);
		i++;
	}
	return (true);
}

t_redirect	*init_redir(char *file, t_token_type type, t_context *ctx)
{
	char		*buf_file;
	t_redirect	*red;

	red = ft_calloc(1, sizeof (t_redirect));
	if (!red)
		fatal_error("malloc");
	buf_file = ft_strdup(file);
	if (!buf_file)
		fatal_error("malloc");
	str_expander(&file, ctx);
	if (ft_strcmp(file, "") == 0 || !is_whitespace(file))
	{
		ft_dprintf(1, "minishell: %s: ", buf_file);
		ft_dprintf(1, "ambiguous redirect\n");
		ctx->sys_error = 1;
	}
	red->file = file;
	red->type = type;
	free(buf_file);
	return (red);
}

void	free_redir(void	*content)
{
	t_redirect	*redir;

	redir = (t_redirect *)content;
	//printf("[%p]\n", redir);
	free(redir->file);
	free(content);
}

static void		add_redirect(t_context *ctx, t_list **redirect, t_token **lst)
{
	char	*file;

	if (!lst || !*lst || !(*lst)->next)
		return;
	file = ft_strdup((*lst)->next->word);
	if ((*lst)->type == TK_REDIR_IN)
		ft_lstadd_back(redirect, ft_lstnew(init_redir(file, TK_REDIR_IN, ctx)));
	if ((*lst)->type == TK_REDIR_OUT)
		ft_lstadd_back(redirect, ft_lstnew(
				init_redir(file, TK_REDIR_OUT, ctx)));
	if ((*lst)->type == TK_REDIR_HEREDOC)
		read_heredoc(ctx, (*lst)->next->word, redirect);
	if ((*lst)->type == TK_REDIR_APPEND)
		ft_lstadd_back(redirect, ft_lstnew(
				init_redir((*lst)->next->word, TK_REDIR_APPEND, ctx)));
	*lst = (*lst)->next->next;
}

t_ast	*arrange_node(t_context *ctx, t_ast *node)
{
	t_token	*lst = node->lst;
	t_token	head;
	t_token	*cur;

	if (!lst)
		return (NULL);
	head.next = NULL;
	cur = &head;
	while (lst)
	{
		if (is_redirect(lst) && expect(lst->next, TK_WORD))
		{
			add_redirect(ctx, &node->redir_lst, &lst);
			continue;
		}
		cur->next = token_copy(lst);
		cur = cur->next;
		lst = lst->next;
	}
	node->argv = head.next;
	return (node);
}

bool	is_redirect(t_token *lst)
{
	if (!lst)
		return (false);
	return ((1 << lst->type) & 0b1111);
}
