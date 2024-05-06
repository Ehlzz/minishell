/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:00:49 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 13:07:24 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

void	*btree_search_item(t_btree *root, void *data_ref,
			int (*cmpf)(void *, void *))
{
	t_btree	*node;
	int		diff;

	node = NULL;
	if (root->left)
		node = btree_search_item(root->left, data_ref, cmpf);
	if (node)
		return (node);
	diff = cmpf(data_ref, root->item);
	if (diff == 0)
		return (root);
	if (root->right)
		node = btree_search_item(root->right, data_ref, cmpf);
	return (node);
}
