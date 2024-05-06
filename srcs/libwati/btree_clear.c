/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:14:58 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/18 16:32:56 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libwati.h"

void	btree_clear(t_btree *root, void (*f)(void *ptr))
{
	if (!root || !f)
		return ;
	btree_clear(root->left, f);
	btree_clear(root->right, f);
	if (root->item)
		f(root->item);
	free(root);
}
