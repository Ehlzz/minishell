/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:19:19 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/17 11:38:11 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>

static void	wati_echo_w(char **strs);
static void	wati_echo_n(char **strs);

void	wati_echo(char **strs)
{
	if (!*strs)
		return ;
	if (wati_strncmp(*strs, "echo", 5))
	{
		wati_putendl_fd("echo: wrong command choice", 2);
		return ;
	}
	strs++;
	if (!*strs)
		return ;
	if (!wati_strncmp(*strs, "-n", 3))
		wati_echo_w(strs);
	else
		wati_echo_n(strs);
}

static void	wati_echo_w(char **strs)
{
	if (!*strs)
		return ;
	strs++;
	while (*strs)
	{
		wati_putstr_fd(*strs, 1);
		strs++;
		if (*strs)
			wati_putchar_fd(' ', 1);
	}
}

static void	wati_echo_n(char **strs)
{
	while (*strs)
	{
		wati_putstr_fd(*strs, 1);
		strs++;
		if (*strs)
			wati_putchar_fd(' ', 1);
	}
	wati_putchar_fd('\n', 1);
}
