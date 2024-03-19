/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehalliez <ehalliez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:30:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/19 17:56:32 by ehalliez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <wati_typedef.h>
# include <wati_const.h>
# include <libwati.h>
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
char	*find_environment_variable(t_list *env_lst, char *to_find);

void	print(void *str);

int		is_char_operator(char c);

t_list	*init_parsing(char *line, t_list *env_lst);
t_list	*create_env_list(char **env);

/*    Manage env    */
t_list	*env_getlist(char **envp);
void	env_print(t_list *env);
char	*env_search(t_list *env, char *var);
t_list	*env_add(t_list **env, char *str);
void	env_delete(t_list	**env, char *find);
/*        Tools         */
void	print_endl(void *ptr);
t_list	*get_var(t_list *list, char *var);
char	*get_name(const char *str);
t_list	*get_vat_prev(const t_list *list, char *find);

/*    Manage dir    */
void	wati_chdir(t_list **env, const char *dir_name);
void	update_pwd(t_list **env);
void	print_pwd(void);

/*    Builtin echo    */
void	wati_echo(char **strs);

/*    wati_readline    */
char	*wati_readline(t_list *env, char *exec);
/*    Manage prompt    */
char	*wati_prompt(t_list *env, char *exec);

t_list	*parsing(char *str);
char	*quote_manager(char **ptr);
int		is_operator_char(char c);

void	set_readline_signal(void);

#endif
