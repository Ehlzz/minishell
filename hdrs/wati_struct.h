/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:22:11 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/23 16:04:45 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATI_STRUCT_H
# define WATI_STRUCT_H

# include <stdbool.h>
# include "wati_typedef.h"

typedef struct s_test
{
	bool	quote;
}	t_test;

typedef struct s_token
{
	t_string	str;
	t_oper		oper;
}	t_token;

typedef struct s_fds
{
	t_fd	in;
	t_fd	out;
}	t_fds;

typedef struct s_cmd
{
	t_oper		oper;
	t_string	*strs;
	t_fds		fds;
}	t_cmd;

typedef struct s_exec
{
	t_string	path;
	t_string	*strs;
	t_string	*envp;
}	t_exec;

#endif