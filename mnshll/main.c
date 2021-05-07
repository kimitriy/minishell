/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:44:53 by rburton           #+#    #+#             */
/*   Updated: 2021/05/07 14:45:38 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int argc, char **argv, char **envp, char **apple) // make a copy of envp!
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	
    char    *line;
    t_set	*s;

    if (!(s = (t_set*)malloc(1 * sizeof(t_set))))
		err_message("t_big malloc error");
	save_argv(s, argv[0]);
    make_env(s, envp); //makes env
	write(1, "waiting for a new command\n", 27);
	while (get_next_line(0, &line))
	{
		lexer(line);
		mini_prsr(s, line); //makes set
		// print_set(s);
		mnshll_execute(s);
        write(1, "minishell-1.0$ ", 15);
	}
	write(1, "waiting for a new command\n", 27);
	return 0;
}
