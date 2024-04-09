/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:30:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/26 16:52:46 by marvin           ###   ########.fr       */
=======
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:30:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/04/08 16:26:34 by bedarenn         ###   ########.fr       */
>>>>>>> bedarenn
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <wati_const.h>
# include <wati_struct.h>
# include <libwati.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libwati.h>

char	*ft_join_args(t_string *argv);
char	*skip_space(t_string *line);
char	*get_word(t_string *line, t_test *test);
char	*get_next_token(t_string *line, t_test *test);
char	*find_variable(t_list *env_lst, t_string to_find);

void	print(void *str);

t_oper	is_operator(t_string s);
char	*get_operator(t_string s);
void	fprint_operator(t_oper oper, t_fd fd);
void	print_token(void *ptr);

int		is_dollar_operator(t_string line);
char	*verify_token(t_string line, t_list *env_lst);
int		count_dollars(t_string line);

t_list	*init_parsing(t_string line, t_list *env_lst);
t_list	*create_env_list(t_string *env);

/*    Manage env    */
t_list	*env_getlist(t_string *envp);
void	env_print(t_list *env);
char	*env_search(t_list *env, t_string var);
t_list	*env_add(t_list **env, t_string str);
void	env_delete(t_list	**env, t_string find);
/*        Tools         */
void	print_endl(void *ptr);
t_list	*get_var(t_list *list, t_string var);
char	*get_name(const t_string str);
t_list	*get_vat_prev(const t_list *list, t_string find);

/*    Manage dir    */
void	wati_chdir(t_list **env, const t_string dir_name);
void	update_pwd(t_list **env);
void	print_pwd(void);

/*    Builtin echo    */
void	wati_echo(t_string *strs);

/*    wati_readline    */
char	*wati_readline(t_list *env, t_string exec);
/*    Manage prompt    */
char	*wati_prompt(t_list *env, t_string exec);

t_list	*parsing(t_string str);
char	*quote_manager(t_string *ptr);
int		is_operator_char(char c);

void	set_readline_signal(void);

<<<<<<< HEAD
t_list	*wildcard(char *where);	
=======
/*    Manage Token    */
t_token	*new_token(t_string token);
t_token	*get_token(t_list *list);
/*    Manage CMD    */
t_cmd	*new_cmd(t_list **lst, t_fds fds);
t_cmd	*get_cmd(t_btree *node);
void	print_cmd(void *ptr);
void	print_cmd_by_level(void *ptr, int level, int is_first_elem);
void	free_cmd(void *ptr);

/*    Binary Tree    */
t_list	*btree_build(t_btree **root, t_list *list);
	/*    OPER    */
t_btree	*btree_node_oper(t_token *token, t_fds fds);
	/*    CMD    */
t_btree	*add_cmd(t_btree **root, t_btree *node);
t_btree	*new_root(t_btree **root, t_btree *node);
t_bool	in_command(t_token *token);

/*    Open Read    */
void	open_read(t_fds *fds, t_list *list);
/*    Open Write    */
void	open_write(t_fds *fds, t_list *list, int flags);
>>>>>>> bedarenn

#endif
