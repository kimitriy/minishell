/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:48:17 by rburton           #+#    #+#             */
/*   Updated: 2021/04/09 19:44:35 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_message(char *error)
{
    write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    exit(0);
}

void	make_cmd(t_big *b)
{
	char *cmd = "pwd";
	
	mini_prsr(b, cmd);
	if (!(b->cmd = (char**)malloc(1 * sizeof(char*))))
		err_message("cmd malloc error");
}

void	make_env(t_big *b, char **envp)
{
	if (!(b->env = (char**)malloc(1 * sizeof(char*))))
		err_message("cmd malloc error");
}

void	make_big(t_big *b, char **envp)
{
	make_cmd(b);
	make_env(b, envp);
}

int		main(char *argc, char **argv, char **envp)
{
	t_big	*b;

	(void)argc;
	(void)argv;

	if (!(b = (t_big*)malloc(1 * sizeof(t_big))))
		err_message("t_big malloc error");

	make_big(b, envp);

	return (0);
}