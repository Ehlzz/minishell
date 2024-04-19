/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:24:48 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/21 22:21:42 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;	

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (0);
	list->content = (void *)content;
	list->next = 0;
	return (list);
}
