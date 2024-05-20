/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:56:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 17:16:49 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "minishell.h"

t_fd	open_read(t_string str, int flags)
{
	t_fd	file;

	file = -1;
	if (is_star(str))
	{
		wati_error(1, "minishell: ambiguous redirect", 2);
		return (file);
	}
	file = open(str, flags);
	if (file < 0)
	{
		if (!access(str, F_OK))
			wati_error(1, "permission denied: %s", str);
		else
			wati_error(1, "no such file or directory: %s", str);
	}
	return (file);
}
