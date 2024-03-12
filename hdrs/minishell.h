/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:30:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/12 20:43:55 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libwati.h>

typedef struct s_test
{
	bool	quote;
}	t_test;

// #### PARSING ### // 

char	*ft_join_args(char **argv);
char	*get_operator(char **line);
char	*skip_space(char **line);
char	*get_word(char **line, t_test *test);
char	*get_next_token(char **line, t_test *test);

void	print(void *str);

int		is_char_operator(char c);

t_list	*init_parsing(char *line);

#endif