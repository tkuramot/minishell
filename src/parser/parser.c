/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:57:29 by tkuramot          #+#    #+#             */
/*   Updated: 2023/09/19 21:25:04 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "utils.h"

static bool	expect_pipe(t_token *lst)
{
	if (!lst || !lst->next)
		return (false);
	return (ft_strcmp(lst->next->word, "|") == 0);
}

static t_redirect	*redirect_init(char *file, t_token_type type)
{
	t_redirect	*red;

	red = ft_calloc(1, sizeof (t_redirect));
	if (!red)
		fatal_error("malloc");
	red->file = file;
	red->type = type;
	return (red);
}

static bool		add_redirect(t_list **redirect, t_token **lst)
{
	if (!lst || !*lst || !(*lst)->next)
		return (false);
	if ((*lst)->type == TK_REDIR_IN)
		ft_lstadd_back(redirect, ft_lstnew(redirect_init((*lst)->next->word, TK_REDIR_IN)));
	if ((*lst)->type == TK_REDIR_OUT)
		ft_lstadd_back(redirect, ft_lstnew(redirect_init((*lst)->next->word, TK_REDIR_OUT)));
	if ((*lst)->type == TK_REDIR_HEREDOC)
		ft_lstadd_back(redirect, ft_lstnew(redirect_init((*lst)->next->word, TK_REDIR_HEREDOC)));
	if ((*lst)->type == TK_REDIR_APPEND)
		ft_lstadd_back(redirect, ft_lstnew(redirect_init((*lst)->next->word, TK_REDIR_APPEND)));
	*lst = (*lst)->next->next;
	return (true);
}

static void		arrange_node(t_ast *ast)
{
	t_token	*lst = ast->lst;
	t_token	*tmp;
	t_token	head;
	t_token	*cur;

	if (!lst)
		return;
	tmp = ast->lst;
	head.next = NULL;
	cur = &head;
	while (tmp)
	{
		if ((1 << tmp->type) & 0b1111)
		{
			add_redirect(&ast->redir_lst, &tmp);
			continue;
		}
		cur->next = token_copy(tmp);
		cur = cur->next;
		tmp = tmp->next;
	}
	ast->argv = head.next;
}

static t_ast	*parse_cmd(t_token **lst)
{
	t_ast	*node;
	t_token	*cmd;
	t_token	*tmp;

	if (!lst || !*lst)
		return (NULL);
	cmd = *lst;
	tmp = *lst;
	while (tmp->next && !expect_pipe(tmp))
		tmp = tmp->next;
	*lst = tmp->next;
	tmp->next = NULL;
	node = ast_new_node_cmd(cmd);
	arrange_node(node);
	return (node);
}

t_ast	*parse_token(t_token *lst)
{
	t_ast	*node;

	node = parse_cmd(&lst);
	if (!node)
		fatal_error("malloc");
	while (true)
	{
		if (lst && ft_strcmp(lst->word, "|") == 0)
		{
			lst = lst->next;
			node = ast_new_node(ND_PIPE, node, parse_cmd(&lst));
		}
		else
			return (node);
	}
	return (parse_token(lst));
}
