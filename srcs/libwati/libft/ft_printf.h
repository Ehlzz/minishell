/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:00:36 by ehalliez          #+#    #+#             */
/*   Updated: 2023/11/30 19:34:25 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putnbr_base(long long int nb, char *hex, long long int base);
int	ft_check_param(char *str, va_list param, int i);
int	ft_print_adress(unsigned long long int nb, char *hex, \
unsigned long long int base);

#endif
