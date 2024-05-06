/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:50:04 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 12:59:20 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

void	btree_insert_data(t_btree **root, void *item,
			int (*cmpf)(void *, void *))
{
	int	diff;

	if (!root || !item || !cmpf)
		return ;
	if (!*root)
		*root = btree_create_node(item);
	else
	{
		diff = cmpf(item, (*root)->item);
		if (diff < 0)
			btree_insert_data(&(*root)->left, item, cmpf);
		else
			btree_insert_data(&(*root)->right, item, cmpf);
	}
}
