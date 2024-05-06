/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:02:29 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/10 16:56:46 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"

char	*wati_readline(t_list *env)
{
	char	*prompt;
	char	*line;

	prompt = wati_prompt(env);
	if (prompt)
		line = readline(prompt);
	else
		line = readline("Minishell>");
	free(prompt);
	return (line);
}
