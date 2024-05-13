/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:22:11 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/13 16:12:44 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATI_STRUCT_H
# define WATI_STRUCT_H

# include <stdbool.h>

# include "libwati.h"
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

typedef struct s_files
{
	t_string	r_in;
	t_fd		h_in;
	t_string	r_out;
	t_string	h_out;
}	t_files;

typedef struct s_fds
{
	t_fd	in;
	t_fd	out;
}	t_fds;

typedef struct s_cmd
{
	t_oper	oper;
	t_list	*strs;
	t_files	files;
	t_bool	is_sub;
}	t_cmd;

typedef struct s_exec
{
	t_string	path;
	t_string	*strs;
	t_string	*envp;
}	t_exec;

typedef struct s_pipe
{
	t_fd	pipe[2];
	t_fd	in;
}	t_pipe;

typedef struct s_shell
{
	t_btree	*root;
	t_list	*env;
	char	**envp;
}	t_shell;

#endif