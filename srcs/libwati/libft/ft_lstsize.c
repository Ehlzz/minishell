/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:46:59 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/21 22:23:59 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*start;
	int		i;

	if (lst)
	{
		i = 1;
		start = lst;
		while (start->next != NULL)
		{
			i++;
			start = start->next;
		}
		return (i);
	}
	return (0);
}
