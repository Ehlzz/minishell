/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:23:25 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 13:30:14 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

int	btree_level_count(t_btree *root)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	if (root->left)
		left += btree_level_count(root->left) + 1;
	if (root->right)
		right += btree_level_count(root->right) + 1;
	if (left > right)
		return (left);
	return (right);
}
