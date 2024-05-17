/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:19:19 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/16 19:45:13 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_first_arg(t_string str);
static void		_wati_echo(t_string *strs);

void	wati_echo(t_string *strs)
{
	t_bool	is_bs;

	if (!*strs)
		return ;
	if (wati_strncmp(*strs, "echo", 5))
	{
		wati_error("echo: wrong command choice");
		return ;
	}
	strs++;
	if (!*strs)
		return ;
	is_bs = check_first_arg(*strs);
	if (!is_bs)
		strs++;
	_wati_echo(strs);
	if (is_bs)
		wati_putchar_fd('\n', 1);
}

static t_bool	check_first_arg(t_string str)
{
	if (*str == '-' && *(str + 1) == '\0')
		return (TRUE);
	if (*str != '-')
		return (TRUE);
	str++;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (FALSE);
	return (TRUE);
}

static void	_wati_echo(t_string *strs)
{
	while (*strs)
	{
		wati_putstr_fd(*strs, 1);
		strs++;
		if (*strs)
			wati_putchar_fd(' ', 1);
	}
}
