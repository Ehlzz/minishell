/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:30:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/18 14:39:34 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <wati_typedef.h>
# include <wati_const.h>
# include <libwati.h>

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
