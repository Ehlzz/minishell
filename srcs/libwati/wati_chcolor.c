/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_chcolor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:14:52 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/18 14:22:30 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <stdlib.h>

char	*wati_chcolor(char *str, char *color)
{
	char	*s1;
	char	*s2;

	if (!str || !color)
		return (NULL);
	s1 = wati_strjoin(color, str);
	s2 = wati_strjoin(s1, NC);
	free(s1);
	return (s2);
}
