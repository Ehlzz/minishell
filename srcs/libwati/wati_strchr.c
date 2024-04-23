/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_strchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:27:59 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/21 17:06:25 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

char	*wati_strchr(const char *s, int c)
{
	return (wati_memchr(s, c, wati_strlen(s) + 1));
}
