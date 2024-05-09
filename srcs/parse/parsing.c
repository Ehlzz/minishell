/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:39:42 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/09 13:44:35 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*modify_token(char *line, t_list *env_lst)
{
	char	*start;
	char	*end;
	char	*tmp;
	int		dollar_count;

	dollar_count = count_dollars(line);
	while (dollar_count)
	{
		start = start_to_dollar(line);
		tmp = dollar_to_dollar(line);
		end = find_variable(env_lst, tmp);
		free(tmp);
		tmp = wati_strjoin(start, end);
		free(start);
		start = tmp;
		end = dollar_to_end(line);
		tmp = wati_strjoin(start, end);
		free(start);
		free(end);
		free(line);
		line = tmp;
		dollar_count--;
	}
	return (remove_quote(line));
}

char	*verify_token(char *line, t_list *env_lst)
{
	if (!line)
		return (NULL);
	return (modify_token(line, env_lst));
}

t_list	*init_parsing(t_string line)
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
