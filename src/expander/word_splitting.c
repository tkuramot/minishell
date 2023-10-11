/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:13:02 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/11 16:30:06 by tsishika         ###   ########.fr       */
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
	if (!new_word)
		return (NULL);
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

static t_token	*create_trimmed_token_list(t_token *argv)
{
	size_t	start;
	t_token	*new;
	t_token	*head;

	start = 0;
	head = create_trimmed_token(argv->word, &start);
	while (argv->word[++start])
	{
		new = create_trimmed_token(argv->word, &start);
		token_add_back(head, new);
	}
	argv = argv->next;
	while (argv)
	{
		start = -1;
		while (argv->word[++start])
		{
			new = create_trimmed_token(argv->word, &start);
			token_add_back(head, new);
		}
		argv = argv->next;
	}
	return (head);
}

void	word_split(t_token **token_lst)
{
	t_token	*buf;
	t_token	*lst;

	lst = *token_lst;
	buf = create_trimmed_token_list(lst);
	*token_lst = buf;
}
