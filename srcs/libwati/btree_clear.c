/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:14:58 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/22 12:52:58 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libwati.h"

static void	_btree_clear(t_btree *root, void (*f)(void *ptr));

void	btree_clear(t_btree **root, void (*f)(void *ptr))
{
	if (!root || !f)
		return ;
	_btree_clear(*root, f);
}

static void	_btree_clear(t_btree *root, void (*f)(void *ptr))
{
	if (!root)
		return ;
	_btree_clear(root->left, f);
	_btree_clear(root->right, f);
	if (root->item)
		f(root->item);
	free(root);
}
