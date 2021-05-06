/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:19:44 by rburton           #+#    #+#             */
/*   Updated: 2021/05/06 23:15:19 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bltn_check(t_set *s, int pi, int ci)
{
	char	*bltins[8] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (NULL != str_in_arr(bltins, s->set[pi].ppline[ci].cmnd[0]))
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
	
	
	pi = -1;
	while (++pi < s->pn)
	{
		ci = -1;
		if (s->set[pi].cn > 1)
			pipes_node(s, pi);
		else
		{
			while (++ci < s->set[pi].cn)
			{
				if (bltn_check(s, pi, ci) == 1)
					bltn_node(s, pi, ci);
				else
					single_cmnd_node(s, pi, ci);
			}
		}
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
		while (++pi < s->set[si].pn)
			if (NULL != str_in_arr(bltins, s->set[si].ppline[pi].cmnd[0]))
				bltn_node(s, si, pi);
			else
				cmnd_node(s, si, pi);
	}
}
*/