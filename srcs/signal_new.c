/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:54:10 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/23 15:48:25 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

static void	sig(int code);

void	set_readline_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig);
	signal(SIGQUIT, sig);
}

static void	sig(int code)
{
	if (code == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
