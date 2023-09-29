/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:12:17 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/29 18:49:30 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

static t_redirect	*init_redir(char *file, t_token_type type)
{
	t_redirect	*red;

	red = ft_calloc(1, sizeof (t_redirect));
	if (!red)
		fatal_error("malloc");
	red->file = file;
	red->type = type;
	return (red);
}

static void		add_redirect(t_list **redirect, t_token **lst)
{
	char	*file;

	if (!lst || !*lst || !(*lst)->next)
		return;
	file = (*lst)->next->word;
	if ((*lst)->type == TK_REDIR_IN)
		ft_lstadd_back(redirect, ft_lstnew(init_redir(file, TK_REDIR_IN)));
	if ((*lst)->type == TK_REDIR_OUT)
		ft_lstadd_back(redirect, ft_lstnew(
				init_redir(file, TK_REDIR_OUT)));
	if ((*lst)->type == TK_REDIR_HEREDOC)
	{
		if (ft_strchr(file, '\'') || ft_strchr(file, '\"'))
			ft_lstadd_back(redirect, ft_lstnew(init_redir(file, TK_REDIR_HEREDOC_Q)));
		else
			ft_lstadd_back(redirect, ft_lstnew(init_redir(file, TK_REDIR_HEREDOC)));
	}
	if ((*lst)->type == TK_REDIR_APPEND)
		ft_lstadd_back(redirect, ft_lstnew(
				init_redir((*lst)->next->word, TK_REDIR_APPEND)));
	*lst = (*lst)->next->next;
}

t_ast	*arrange_node(t_ast *node)
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
			add_redirect(&node->redir_lst, &lst);
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
