/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:32:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/19 17:32:49 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <unistd.h>

t_bool	wati_error(int code, char *format, ...)
{
	va_list	arg;

	va_start(arg, format);
	wati_fprintf(STDERR_FILENO, "%s: Error: ", NAME);
	wati_vfprintf(STDERR_FILENO, format, arg);
	wati_putchar_fd('\n', STDERR_FILENO);
	va_end(arg);
	g_err = code;
	return (FALSE);
}
