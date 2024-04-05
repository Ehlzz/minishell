/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:50 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/04 12:03:56 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

static void	btree_apply_by_level_node(t_btree *node,
				int level,
				void (*applyf)(void *item,
					int current_level,
					int is_first_elem));

void	btree_apply_by_level(t_btree *root,
			void (*applyf)(void *item,
				int current_level,
				int is_first_elem))
{
	if (!root || !applyf)
		return ;
	if (root->left)
		btree_apply_by_level_node(root->left, 1, applyf);
	applyf(root->item, 0, 1);
	if (root->right)
		btree_apply_by_level_node(root->right, 1, applyf);
}

static void	btree_apply_by_level_node(t_btree *node,
				int level,
				void (*applyf)(void *item,
					int current_level,
					int is_first_elem))
{
	if (node->left)
		btree_apply_by_level_node(node->left, level + 1, applyf);
	applyf(node->item, level, 0);
	if (node->right)
		btree_apply_by_level_node(node->right, level + 1, applyf);
}
