/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 05:53:17 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/09 03:11:39 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	verify(char *set, char s1c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*result;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (0);
	end = ft_strlen((char *)s1);
	while (s1[start] && verify((char *)set, s1[start]) == 1)
		start++;
	while (start < end && verify((char *)set, s1[end - 1]) == 1)
		end--;
	result = malloc(sizeof(char) * (end - start + 1));
	if (result == NULL)
		return (0);
	while (s1[start] && start < end)
	{
		result[i] = s1[start];
		i++;
		start++;
	}
	result[i] = 0;
	return (result);
}
