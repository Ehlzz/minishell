/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:05:09 by ehalliez          #+#    #+#             */
/*   Updated: 2024/04/21 17:10:03 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env_print(t_list *env)
{
	while (env)
	{
		if (env->content && wati_strchr(env->content, '='))
			wati_putendl_fd(env->content, 1);
		env = env->next;
	}
}
