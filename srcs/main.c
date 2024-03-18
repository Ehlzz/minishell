/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/18 17:27:40 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int	test_parsing(t_list *env, char *exec);

void	wati_exit(void)
{
	printf("exit\n");
}

void	print(void *str)
{
	wati_putendl_fd((char *)str, 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*exp;
	char	*name;
	char	*content;

	env = env_getlist(envp);
	if (argc == 2)
	{
		exp = wati_strdup(argv[1]);
		env_add(&env, exp);
		name = get_name(exp);
		content = env_search(env, name);
		printf("%s = %s\n", name, content);
		env_delete(&env, name);
		printf("%s\n", env_search(env, name));
		free(name);
		free(content);
	}
	else if (argc > 0)
		return (test_parsing(env, *argv));
	wati_chdir(&env, "srcs");
	wati_chdir(&env, "srcs");
	print_pwd();
	wati_lstclear(&env, free);
	return (0);
}

int	test_parsing(t_list *env, char *exec)
{
	char	*input;
	t_list	*list;

	set_readline_signal();
	while (1)
	{
		input = wati_readline(env, exec);
		if (!input)
			break ;
		if (!wati_strncmp(input, "exit", 5))
			break ;
		list = parsing(input);
		if (list)
		{
			wati_lstiter(list, print);
			wati_lstclear(&list, free);
		}
		free(input);
	}
	if (input)
		free(input);
	wati_lstclear(&env, free);
	return (1);
}
