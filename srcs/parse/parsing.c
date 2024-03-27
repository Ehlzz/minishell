/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:39:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/27 14:59:15 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_parsing(t_string line, t_list *env_lst)
{
	t_string	word;
	t_token		*token;
	t_string	str;
	t_list		*lst;
	t_test		test;

	lst = NULL;
	test.quote = false;
	str = line;
	while (*line)
	{
		word = get_next_token(&line, &test);
		word = verify_token(word, env_lst);
		if (!word)
			break ;
		token = new_token(word);
		wati_lstadd_back(&lst, wati_lstnew(token));
	}
	free(str);
	if (test.quote)
	{
		wati_lstclean(&lst);
		wati_putstr_fd("error: quote (test)\n", 2);
		return (NULL);
	}
	return (lst);
}
