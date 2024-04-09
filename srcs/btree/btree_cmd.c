/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:58:14 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/05 13:58:50 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*new_root(t_btree **root, t_btree *node)
{
	node->left = *root;
	*root = node;
	return (*root);
}

t_btree	*add_cmd(t_btree **root, t_btree *node)
{
	t_btree	*ptr;

	if (!*root)
		*root = node;
	else
	{
		ptr = *root;
		while (ptr->right)
			ptr = ptr->right;
		ptr->right = node;
	}
	return (*root);
}
