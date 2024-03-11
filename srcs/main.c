/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/11 20:34:14 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libwati.h>

char	*ft_join_args(char **argv)
{
	char	*tmp;
	char	*result;
	int		i;
	
	i = 1;
	tmp = NULL;
	result = wati_strdup(argv[1]);
	while (argv[i])
	{
		if (argv[i + 1])
		{
			tmp = result;
			result = wati_strjoin(tmp, " ");
			free(tmp);
			tmp = result;
			result =  wati_strjoin(tmp, argv[i + 1]);
			free(tmp);
		}
		i++;
	}
	return (result);
}

void print(void *str)
{
	wati_putendl_fd(str, 1);
}

char	*get_next_word(char **str)
{
	int		i;
	int		len;
	char	*str0;
	
	i = 0;
	len = 0;
	str0 = *str;
	while (**str)
	{
		if (**str != ' ')
			len++;
		else 
			break;
		*str++;
	}
	return (wati_substr(str0, 0, len));
}

int	main(int argc, char **argv)
{
	char	*str;
	t_list *lst;
	
	(void)argc;
	lst = NULL;
	str = ft_join_args(argv);
	while (*str)
		wati_lstadd_back(&lst, wati_lstnew(get_next_word(&str)));
	wati_lstiter(lst, print);
	free(str);
	return (0);
}
