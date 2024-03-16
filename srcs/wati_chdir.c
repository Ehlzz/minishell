/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_chdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:43:19 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/15 16:25:24 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libwati.h>
#include <minishell.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	wati_chdir(void)
{
	chdir("/nfs/homes/bedarenn/Documents/Minish/srcs");
	printf("%s\n", getenv("PWD"));
}
