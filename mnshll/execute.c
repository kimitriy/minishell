/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:19:44 by rburton           #+#    #+#             */
/*   Updated: 2021/05/19 23:46:53 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bltn_check(t_set *s, int pi, int ci)
{
	char	*bltins[8] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (NULL != str_in_arr(bltins, s->st[pi].pln[ci].cmd[0]))
	{
		// write(1, "yes", 3);
		return(1);
	}
	else
	{	
		// write(1, "no", 2);
		return(0);
	}
}

void	mnshll_execute(t_set *s)
{
	int		pi; //pipeline indx
	int		ci; //command indx
	
	// printf("s->st[0].pln[0].cmd[0]: %s\n", s->st[0].pln[0].cmd[0]);
	// printf("s->st[0].pln[0].cmd[1]: %s\n", s->st[0].pln[0].cmd[1]);
	// printf("s->st[1].pln[0].cmd[0]: %s\n", s->st[1].pln[0].cmd[0]);
	// printf("s->st[1].pln[0].cmd[1]: %s\n", s->st[1].pln[0].cmd[1]);
	// printf("s->st[2].pln[0].cmd[0]: %s\n", s->st[2].pln[0].cmd[0]);
	// printf("s->st[2].pln[0].cmd[1]: %s\n", s->st[2].pln[0].cmd[1]);

	pi = 0;
	while (pi < s->pn)
	{
		if (s->st[pi].cn > 1)
			pipes_node(s, pi);
		else
		{
			ci = 0;
			while (ci < s->st[pi].cn)
			{
				// printf("s->st[%d].pln[%d].cmd[0]: %s\n", pi, ci, s->st[pi].pln[ci].cmd[0]);
				// printf("s->st[%d].pln[%d].cmd[1]: %s\n", pi, ci, s->st[pi].pln[ci].cmd[1]);
				if (bltn_check(s, pi, ci) == 1)
					bltn_node(s, pi, ci);
				else
					single_cmd_node(s, pi, ci);
				ci++;
			}
		}
		pi++;
	}
}

/*
void	mnshll_execute(t_set *s)
{
	int		si; //set indx
	int		pi; //pipeline indx
	char	*bltins[8] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};
	si = -1;
	while (++si < s->sn)
	{
		pi = -1;
		while (++pi < s->st[si].pn)
			if (NULL != str_in_arr(bltins, s->st[si].pln[pi].cmd[0]))
				bltn_node(s, si, pi);
			else
				cmd_node(s, si, pi);
	}
}
*/