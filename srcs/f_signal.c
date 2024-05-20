/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:04:23 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/20 18:07:57 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "minishell.h"

void	sig_rl(int code)
{
	if (code == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_err = 130;
	}
}

void	sig_here_doc(int code)
{
	if (code == SIGINT)
	{
		g_err = 130;
		printf("\n");
		close(0);
	}
}

void	sig_fork(int code)
{
	if (code == SIGINT)
	{
		printf("\n");
		g_err = 130;
	}
	if (code == SIGQUIT)
	{
		g_err = 131;
		printf("Quit (core dumped)\n");
	}
}
