/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:09 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/21 22:20:59 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**startold;
	t_list	*startnew;
	t_list	*list;	

	if (lst && del && f)
	{
		startold = &lst;
		list = ft_lstnew(f(lst->content));
		startnew = list;
		lst = lst->next;
		while (lst)
		{
			list->next = ft_lstnew(f(lst->content));
			list = list->next;
			lst = lst->next;
		}
		ft_lstclear(startold, del);
		return (startnew);
	}
	return (0);
}
