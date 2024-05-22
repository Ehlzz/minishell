/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:14:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/22 12:53:14 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libwati.h"

static void	_btree_clean(t_btree *root);

void	btree_clean(t_btree **root)
{
	if (!root)
		return ;
	_btree_clean(*root);
}

static void	_btree_clean(t_btree *root)
{
	if (!root)
		return ;
	_btree_clean(root->left);
	_btree_clean(root->right);
	free(root);
}
