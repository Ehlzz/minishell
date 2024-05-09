/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:05:09 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/09 16:49:26 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_char_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

void	env_print(t_string *env)
{
	if (!env)
		return ;
	while (*env)
	{
		if (is_char_equal(*env))
			wati_putendl_fd(*env, 1);
		env++;
	}
}
