/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:54:10 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/17 17:50:32 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "minishell.h"

static void	sig_rl(int code);
static void	sig_here_doc(int code);

void	set_readline_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_rl);
	signal(SIGQUIT, sig_rl);
}

void	set_signal_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_here_doc(void)
{
	signal(SIGINT, sig_here_doc);
	signal(SIGQUIT, sig_here_doc);
}

static void	sig_rl(int code)
{
	if (code == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		error_code = 130;
	}
}

static void	sig_here_doc(int code)
{
	if (code == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		error_code = 130;
		close(0);
	}
}
