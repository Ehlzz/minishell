/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:30:42 by bedarenn          #+#    #+#             */
/*   Updated: 2024/05/16 14:00:23 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include <wati_const.h>
# include <wati_struct.h>

extern gtype_t	error_code;

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

// #### PARSING ### // 

int		is_char_operator(char c);
char	*ft_join_args(char **argv);
char	*get_operator_line(char **line);
char	*skip_space(char **line);
char	*get_word(char **line, t_test *test);
char	*get_next_token(char **line, t_test *test);
char	*find_variable(t_list *env_lst, char *to_find);
char	*modify_token(char *line, t_list *env_lst);
char	*verify_token(char *line, t_list *env_lst);
char	*remove_quote(char *str);
int		count_available(char *str);
char	*dollar_to_end(char *line);
char	*dollar_to_dollar(char *line);
char	*start_to_dollar(char *line);
int		here_doc(char *limiter, t_cmd *cmd, t_list **list, t_shell *shell);

// ### TRIE ### //

void	print(void *str);
int		is_dollar_operator(char *line);
char	*verify_token(char *line, t_list *env_lst);
int		count_dollars(char *line);

t_list	*init_parsing(char *line);
t_list	*wildcard_search(char *search);
t_list	*create_env_list(char **env);
int		wildcard_checker(char *search, char *content);
int		is_star(char *str);
t_list	*convert_strs(t_list *strs, t_list *env);

/*    Manage env    */
t_list	*env_getlist(t_string *envp);
void	env_print(t_list *env);
char	*env_search(t_list *env, t_string var);
t_list	*env_add(t_list **env, t_string str);
void	env_delete(t_list	**env, t_string find);
/*        Tools         */
void	print_endl(void *ptr);
t_list	*get_var(t_list *list, t_string var);
t_list	*get_var_not_assigned(const t_list *list, t_string find);
char	*get_name(const t_string str);
t_list	*get_vat_prev(const t_list *list, t_string find);
t_list	*get_vat_prev_w_equal(const t_list *list, t_string find);

/*    Manage dir    */
void	wati_chdir(t_list **env, const t_string dir_name);
void	update_pwd(t_list **env);
void	print_pwd(void);

/* Builtin export */
void	export(t_list *env, char **strs);
int		verif_identifier(char *str);
void	export_concat(t_list *env, char *str);
void	__export_concat(t_list *env, char *name, char *str);
int		is_char_before_char(char *str, int find, int until);
int		strlen_to_char(char *str, int c);
char	*add_quote(char *str);
int		is_char_equal(char *str);

/*    Builtin echo    */
void	wati_echo(t_string *strs);

/*    wati_readline    */
char	*wati_readline(t_list *env);
/*    Manage prompt    */
char	*wati_prompt(t_list *env);
/*    wati_error    */
t_bool	wati_error(char *format, ...);

t_list	*parsing(t_string str);
char	*quote_manager(t_string *ptr);
int		is_operator_char(char c);

void	set_readline_signal(void);
void	set_signal_fork(void);

/*    Manage Token    */
t_token	*new_token(t_string token);
t_token	*get_token(t_list *list);
void	free_token(void *ptr);
/*    Manage CMD    */
t_cmd	*get_cmd(t_btree *node);
void	print_cmd_by_level(void *ptr, int level, int is_first_elem);
void	free_cmd(void *ptr);
void	free_exec(void *ptr);

/*    Binary Tree    */
t_bool	btree_build(t_btree **root, t_list *list, t_shell *shell);
t_bool	_btree_build_oper(t_btree **root, t_list **list);
t_bool	_btree_build_pipe(t_btree **root, t_list **list, t_shell *shell);
t_bool	btree_par(t_btree **root, t_list **list, t_shell *shell);
t_bool	btree_oper(t_btree **root, t_list **list);
t_bool	btree_pipe(t_btree **root, t_list **list, t_shell *shell);
t_bool	btree_cmd(t_btree **root, t_list **list, t_shell *shell);
	/*    Tools    */
t_bool	is_opercmd(t_oper oper);
t_btree	*new_root(t_btree **root, t_btree *node);
t_btree	*add_root(t_btree **root, t_btree *node);
		/*    CMD    */
t_btree	*add_cmd(t_btree **root, t_btree *node);
t_bool	in_command(t_token *token);

/*    Open Read    */
t_fd	open_read(t_string str, int flags);
/*    Open Write    */
t_fd	open_write(t_string str, int flags);

void	wati_close(t_fd fd);
void	close_fds(t_fds fds);
void	close_pipe(int pipe[2]);
void	close_spipe(t_pipe fd);

t_bool	add_file(t_list	**files, t_oper oper, t_string file);
t_bool	add_fd(t_list	**files, t_oper oper, t_fd fd);

void	swap_spipe(t_pipe *fd);

t_bool	wati_dup_files(t_list *files, t_pipe *fd);
t_pipe	reset_pipe(void);

t_list	*add_pid(t_list **list, pid_t pid);
t_bool	wait_pids(t_list *list);

/*    EXEC    */
t_bool	wati_exec(t_shell shell);
t_bool	_wati_exec(t_btree *node, t_pipe fd, t_shell *shell);
t_bool	wati_execve(t_cmd *cmd, t_pipe *fd, t_list **pids, t_shell *shell);
t_bool	wati_pipe(t_btree *node, t_pipe fd, t_shell *shell);
t_bool	_wati_pipe_oper(t_btree *node, t_pipe *fd,
			t_list **pids, t_shell *shell);
char	*get_path(t_string cmd, t_list *env);

#endif
