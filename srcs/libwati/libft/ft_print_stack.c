/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:11:21 by ehalliez          #+#    #+#             */
/*   Updated: 2023/12/18 02:15:06 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_stack(int **stack, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%d\n", (*stack)[i]);
		i++;
	}
	write(1, "\n", 1);
}
