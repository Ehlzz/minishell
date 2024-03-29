/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:31:28 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/29 12:51:38 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

t_word	*new_word(t_string str)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->str = str;
	word->oper = is_operator(str);
	return (word);
}

t_word	*getc_word(t_list *list)
{
	return (list->content);
}
