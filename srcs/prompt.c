/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:25:38 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/15 16:04:25 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <minishell.h>
#include <unistd.h>

char	*get_prompt(void)
{
	static char	*prompt;

	prompt = getcwd(NULL, 0);
	return (prompt);
}
