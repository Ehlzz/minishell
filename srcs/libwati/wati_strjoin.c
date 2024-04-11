/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:21:13 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/11 20:01:26 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <stdlib.h>

char	*wati_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	len1;
	size_t	len2;
	char	*s;

	if (!s1)
		return (wati_strdup(s2));
	if (!s2)
		return (wati_strdup(s1));
	len1 = wati_strlen(s1);
	len2 = wati_strlen(s2);
	len = len1 + len2;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	wati_memcpy(s, s1, len1);
	wati_memcpy(s + len1, s2, len2);
	s[len] = '\0';
	return (s);
}
