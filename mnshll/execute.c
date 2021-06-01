/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:19:44 by rburton           #+#    #+#             */
/*   Updated: 2021/05/31 20:59:37 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bltn_check(t_set *s, int pi, int ci)
{
	char	*bltins[8] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (NULL != str_in_arr(bltins, s->st[pi].pln[ci].cmd[0]))
		return(1);
	else
		return(0);
}

void	mnshll_execute(t_set *s)
{
	int		pi; //pipeline indx
	int		ci; //command indx
	
	pi = 0;
	while (pi < s->pn)
	{
		if (s->st[pi].cn > 1)
		{
			write(1, "pipes_node(s, pi)\n", 18);
			pipes_node(s, pi);
		}
		else
		{
			ci = 0;
			while (ci < s->st[pi].cn)
			{
				if (bltn_check(s, pi, ci) == 1)
				{
					write(1, "bltn_node(s, pi, ci)\n", 21);
					bltn_node(s, pi, ci);
				}
				else
				{
					write(1, "single_cmd_node(s, pi, ci)\n", 27);
					single_cmd_node(s, pi, ci);
				}
				ci++;
			}
		}
		pi++;
	}
}
