/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:48:54 by ehalliez          #+#    #+#             */
/*   Updated: 2024/03/13 15:59:16 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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