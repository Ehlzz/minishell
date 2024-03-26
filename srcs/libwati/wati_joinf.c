/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_joinf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:45:37 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/18 17:34:17 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static size_t	wati_formatlen(size_t nb, va_list arg);
static char		*wati_formatfill(size_t nb, va_list arg, char *str);

char	*wati_vjoinf(size_t nb, va_list arg)
{
	char	*str;
	size_t	len;
	va_list	cp;

	va_copy(cp, arg);
	len = wati_formatlen(nb, arg);
	str = malloc(sizeof(char ) * (len + 1));
	if (!str)
	{
		va_end(cp);
		return (NULL);
	}
	str[0] = '\0';
	str[len] = '\0';
	wati_formatfill(nb, cp, str);
	va_end(cp);
	return (str);
}

char	*wati_joinf(size_t nb, ...)
{
	va_list	arg;
	char	*str;

	va_start(arg, nb);
	str = wati_vjoinf(nb, arg);
	va_end(arg);
	return (str);
}

static size_t	wati_formatlen(size_t nb, va_list arg)
{
	size_t	len;
	char	*str;

	len = 0;
	while (nb > 0)
	{
		str = va_arg(arg, char *);
		if (str)
			len += wati_strlen(str);
		nb--;
	}
	return (len);
}

static char	*wati_formatfill(size_t nb, va_list arg, char *str)
{
	char	*s;

	while (nb > 0)
	{
		s = va_arg(arg, char *);
		if (s)
			strcat(str, s);
		nb--;
	}
	return (str);
}
