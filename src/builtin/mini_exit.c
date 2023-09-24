/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:10:58 by tsishika          #+#    #+#             */
/*   Updated: 2023/09/24 11:11:06 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtin.h"

int	mini_exit(t_token *lst, t_env *env_lst)
{
	token_lst_free(lst);
	free_all_env_lst(env_lst);
	exit(0);
}

// exit(status)みたいな形で終了すべき？
// exit内でfreeする関数多そう
