/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:05:09 by ehalliez          #+#    #+#             */
/*   Updated: 2024/05/13 21:56:37 by ehalliez         ###   ########.fr       */
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

void	env_print(t_list *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (is_char_equal(env->content))
			wati_putendl_fd(env->content, 1);
		env = env->next;
	}
}
