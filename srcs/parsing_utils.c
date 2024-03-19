/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/19 17:47:41 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '&' || c == '|');
}

#include <minishell.h>

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
