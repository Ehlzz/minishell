/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_typedef.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:28:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/19 17:50:59 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATI_TYPEDEF_H
# define WATI_TYPEDEF_H

# include <sys/stat.h>

typedef struct stat		t_stat;
typedef struct dirent	t_dir;

typedef enum s_bool
{
	ERROR = -1,
	FALSE,
	TRUE,
}	t_bool;

#endif