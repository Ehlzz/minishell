/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_chdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:43:19 by bedarenn          #+#    #+#             */
<<<<<<< HEAD:srcs/builtin/wati_chdir.c
/*   Updated: 2024/03/27 14:46:59 by bedarenn         ###   ########.fr       */
=======
/*   Updated: 2024/04/19 19:11:53 by ehalliez         ###   ########.fr       */
>>>>>>> ehalliez:srcs/builtin/chdir.c
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	wati_chdir(void)
{
	chdir("/nfs/homes/bedarenn/Documents/Minish/srcs");
	printf("%s\n", getenv("PWD"));
}
