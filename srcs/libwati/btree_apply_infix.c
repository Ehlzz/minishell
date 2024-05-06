/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:05 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 12:46:52 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root->left)
		btree_apply_prefix(root->left, applyf);
	applyf(root->item);
	if (root->right)
		btree_apply_prefix(root->right, applyf);
}
