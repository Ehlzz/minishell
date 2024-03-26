/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:02:29 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/18 17:28:05 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <minishell.h>
#include <stdio.h>

char	*wati_readline(t_list *env, char *exec)
{
	char	*prompt;
	char	*line;

	prompt = wati_prompt(env, exec);
	if (prompt)
		line = readline(prompt);
	else
		line = readline("Minishell>");
	free(prompt);
	return (line);
}
