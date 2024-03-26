/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:49:20 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/26 15:35:24 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_char_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

t_list	*create_env_list(char **env)
{
	t_list	*lst;

	lst = NULL;
	while (*env)
	{
		wati_lstadd_back(&lst, wati_lstnew(*env));
		env++;
	}
	return (lst);
}
