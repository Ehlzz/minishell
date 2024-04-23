/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:12:27 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/19 19:12:40 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	wati_putendl_fd(path, 1);
	free(path);
}