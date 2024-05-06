/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:32:32 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/21 12:57:25 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <unistd.h>

t_bool	wati_error(char *format, ...)
{
	va_list	arg;

	va_start(arg, format);
	wati_fprintf(STDERR_FILENO, "%s: Error: ", NAME);
	wati_vfprintf(STDERR_FILENO, format, arg);
	wati_putchar_fd('\n', STDERR_FILENO);
	va_end(arg);
	return (FALSE);
}
