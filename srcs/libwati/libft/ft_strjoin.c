/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:23:59 by ehalliez          #+#    #+#             */
/*   Updated: 2023/12/16 05:40:33 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!str1 || !str2)
		return (0);
	if (!str1)
		return (ft_strdup(str2));
	i = -1;
	s1_len = ft_strlen((char *)str1);
	s2_len = ft_strlen((char *)str2);
	result = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == NULL)
		return (0);
	while (str1[++i])
		result[i] = str1[i];
	i = -1;
	while (str2[++i])
		result[s1_len + i] = str2[i];
	result[s1_len + i] = 0;
	return ((char *)result);
}
