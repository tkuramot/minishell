/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:13:02 by tsishika          #+#    #+#             */
/*   Updated: 2023/10/10 02:29:07 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// int	is_space(char c)
// {
// 	return ((9 <= c && c <= 13) || c == ' ');
// }

// bool	is_whitespace(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if(is_space(str[i]))
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// void	word_split(char *str)
// {
// 	size_t	i;
// 	size_t	start;
// 	size_t	end;
// 	char	new_str;

// 	i = 0;
// 	while(str[i])
// 	{
// 		while(is_space(str[i]) && str[i])
// 			i++;
// 		if(!str[i])
// 			return ;
// 		start = i;
// 		while(!is_space(str[i]) && str[i])
// 			i++;
// 		end = i;
// 		new_str = ft_substr(str, start, end - start + 1);
// 	}
// }
