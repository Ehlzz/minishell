/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:06:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/24 16:31:38 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/wait.h>

t_list	*add_pid(t_list **list, pid_t pid)
{
	pid_t	*ptr;
	t_list	*new;

	ptr = malloc(sizeof(pid_t));
	*ptr = pid;
	new = wati_lstnew(ptr);
	wati_lstadd_back(list, new);
	return (*list);
}

void	wait_pids(t_list *list)
{
	pid_t	*ptr;

	ptr = list->content;
	waitpid(*ptr, NULL, 0);
	free(ptr);
	if (list->next)
		wait_pids(list->next);
	free(list);
}
