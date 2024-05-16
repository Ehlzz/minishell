/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:14:02 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/16 15:02:07 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <stdlib.h>

char	*wati_strdup(const char *s)
{
	char	*p;
	int		s_len;

	s_len = wati_strlen(s) + 1;
	p = malloc(sizeof(char) * s_len);
	if (!p)
		return (NULL);
	p = wati_memcpy(p, s, s_len);
	return (p);
}
