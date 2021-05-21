/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:44:53 by rburton           #+#    #+#             */
/*   Updated: 2021/05/21 10:31:30 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int argc, char **argv, char **envp, char **apple) // make a copy of envp!
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	
    char    *line;
    t_set	*s;


	s = (t_set*)calloc(1, sizeof(t_set));
    // if (!(s = (t_set*)malloc(1 * sizeof(t_set))))
	// 	err_message("t_big malloc error");
	// save_argv(s, argv[0]);
    make_env(s, envp); //makes env
	write(1, "waiting for a new command\n", 27);
	while (get_next_line(0, &line))
	{
		lexer(line);
		mini_prsr(s, line); //makes set
		
		// printf("s->st[0].pln[0].cmd[0]: %s\n", s->st[0].pln[0].cmd[0]);
		// printf("s->st[0].pln[0].cmd[1]: %s\n", s->st[0].pln[0].cmd[1]);
		// printf("s->st[1].pln[0].cmd[0]: %s\n", s->st[1].pln[0].cmd[0]);
		// printf("s->st[1].pln[0].cmd[1]: %s\n", s->st[1].pln[0].cmd[1]);
		// printf("s->st[2].pln[0].cmd[0]: %s\n", s->st[2].pln[0].cmd[0]);
		// printf("s->st[2].pln[0].cmd[1]: %s\n", s->st[2].pln[0].cmd[1]);
		
		mnshll_execute(s);
        write(1, "minishell-1.0$ ", 15);
	}
	write(1, "waiting for a new command\n", 27);
	return 0;
}
