/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:39:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/29 15:57:06 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_parsing(t_string line, t_list *env_lst)
{
	t_string	str;
	t_token		*token;
	t_list		*lst;
	t_test		test;

	lst = NULL;
	test.quote = false;
	while (wati_isspace(*line))
		line++;
	while (*line)
	{
		str = get_next_token(&line, &test);
		str = verify_token(str, env_lst);
		if (!str)
			break ;
		token = new_token(str);
		wati_lstadd_back(&lst, wati_lstnew(token));
	}
	if (test.quote)
	{
		wati_lstclean(&lst);
		wati_putstr_fd("error: quote (test)\n", 2);
		return (NULL);
	}
	return (lst);
}
