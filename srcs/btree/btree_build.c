/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:08:21 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/29 16:01:27 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

t_list	*btree_build(t_btree **root, t_list *list)
{
	t_cmd	*cmd;
	t_fds	fds;

	fds.in = 0;
	fds.out = 1;
	cmd = new_cmd(&list, fds);
	*root = btree_create_node(cmd);
	return (list);
}
