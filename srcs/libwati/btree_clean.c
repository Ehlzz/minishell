/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:14:56 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/02 15:27:00 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libwati.h"

void	btree_clean(t_btree *root)
{
	if (!root)
		return ;
	btree_clean(root->left);
	btree_clean(root->right);
	free(root);
}
