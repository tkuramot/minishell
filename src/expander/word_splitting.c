/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:13:02 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 02:28:37 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	is_space(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

static t_token	*create_trimmed_token(char	*word, size_t *i)
{
	size_t	j;
	char	*new_word;
	t_token	*new;

	while (word[*i] && is_space(word[*i]))
		(*i)++;
	j = *i;
	while (word[j] && !is_space(word[j]))
		j++;
	new_word = ft_substr(word, *i, j - *i);
	// if(!new_word)
		//error
	new = token_init(new_word, TK_WORD);
	*i = j;
	return (new);
}

static void	token_add_back(t_token *head, t_token *new)
{
	if (!head || !new)
		return ;
	while (head->next)
		head = head->next;
	head->next = new;
}

void	create_trimmed_token_list(t_token **argv)
{
	size_t	start;
	t_token	*lst;
	t_token	*new;
	t_token	*head;

	lst = *argv;
	start = 0;
	head = create_trimmed_token(lst->word, &start);
	ft_dprintf(1, "head = %p\n", head);
	while (lst->word[start])
	{
		new = create_trimmed_token(lst->word, &start);
		token_add_back(head, new);
		start++;
	}
	lst = lst->next;
	while (lst)
	{
		start = 0;
		while (lst->word[start])
		{
			new = create_trimmed_token(lst->word, &start);
			token_add_back(head, new);
			start++;
		}
		lst = lst->next;
	}
	*argv = head;
}

void	word_split(t_token **token_lst)
{
	t_token	*lst;

	lst = *token_lst;
	create_trimmed_token_list(&lst);
	*token_lst = lst;
}
