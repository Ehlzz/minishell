/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:54:10 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/15 12:43:48 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

static void	sig_rl(int code);
static void	sig_fork(int code);

void	set_readline_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_rl);
	signal(SIGQUIT, sig_rl);
}

void	set_signal_fork(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_fork);
	signal(SIGQUIT, sig_fork);
}

static void	sig_rl(int code)
{
	if (code == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sig_fork(int code)
{
	(void) code;
}
