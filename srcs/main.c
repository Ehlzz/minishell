/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedarenn <bedarenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:01 by bedarenn          #+#    #+#             */
/*   Updated: 2024/03/16 19:57:34 by bedarenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

void	wati_exit(void)
{
	printf("exit\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*exp;
	char	*name;
	char	*content;

	if (argc != 1 && argc != 2)
		return (1);
	(void)argv;
	//atexit(&wati_exit);
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
	else
		env_print(&env);
	wati_chdir(&env, "srcs");
	wati_chdir(&env, "srcs");
	print_pwd();
	wati_lstclear(&env, free);
	return (0);
}
