/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_typedef.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:28:36 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/14 15:16:53 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATI_TYPEDEF_H
# define WATI_TYPEDEF_H

# include <sys/stat.h>

typedef char *			t_string;
typedef int				t_fd;

typedef struct stat		t_stat;
typedef struct dirent	t_dir;

typedef enum s_builtin
{
	CMD,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtin;

typedef enum s_bool
{
	ERROR = -1,
	FALSE,
	TRUE,
}	t_bool;

typedef enum s_oper
{
	NO,
	PIPE,
	AND,
	OR,
	R_IN,
	R_OUT,
	H_IN,
	H_OUT,
	P_IN,
	P_OUT,
}	t_oper;

#endif