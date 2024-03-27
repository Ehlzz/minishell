/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wati_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:22:11 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/27 14:35:54 by bedarenn         ###   ########.fr       */
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
	t_string	word;
	t_oper		oper;
}	t_token;

#endif