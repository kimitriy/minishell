/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:44:53 by rburton           #+#    #+#             */
/*   Updated: 2021/06/08 14:20:48 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_s(t_set *s)
{
	int		pi;
	int		ci;
	int		i;

	pi = -1;
	while (++pi < s->pn)
	{
		ci = -1;
		while (++ci < s->st[pi].cn)
		{
			i = -1;
			while (++i < s->st[pi].pln[ci].n)
				if (s->st[pi].pln[ci].cmd[i] != NULL)
					free(s->st[pi].pln[ci].cmd[i]);
			if (s->st[pi].pln[ci].cmd != NULL)
				free(s->st[pi].pln[ci].cmd);
		}
		free(s->st[pi].pln);
		if (s->st[pi].fd_arr != NULL)
			ft_free_int(s->st[pi].fd_arr);
		if (s->st[pi].pid_arr != NULL)
			free(s->st[pi].pid_arr);
	}
	free(s->st);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_set	*s;

	s = (t_set *)ft_calloc(1, sizeof(t_set));
	make_env(s, envp); //makes env
	write(1, "minishell: ", 11);
	while (get_next_line(0, &line))
	{
		lexer(line);
		mini_prsr(s, line); //makes set
		print_set(s);
		mnshll_execute(s);
		write(1, "minishell: ", 11);
		clear_s(s);
		free(line);
	}
	write(1, "minishell: ", 11);
	while (1)
	{

	}
	return (0);
}
