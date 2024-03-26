/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:39:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/26 15:32:54 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_parsing(char *line, t_list *env_lst)
{
	char	*token;
	char	*str;
	t_list	*lst;
	t_test	test;

	lst = NULL;
	test.quote = false;
	str = line;
	while (*line)
	{
		token = get_next_token(&line, &test);
		token = verify_token(token, env_lst);
		wati_printf("line = %s\n", token);
		if (!token)
			break ;
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
