/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:44:53 by rburton           #+#    #+#             */
/*   Updated: 2021/06/15 17:32:08 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_st(t_set *s, int pi)
{
	int		ci;
	int		i;

	ci = 0;
	while (ci < s->st[pi].cn)
	{
		i = 0;
		while (i < s->st[pi].pln[ci].n)
		{
			if (s->st[pi].pln[ci].cmd[i] != NULL)
				free(s->st[pi].pln[ci].cmd[i]);
			s->st[pi].pln[ci].cmd[i] = NULL;
			i++;
		}
		if (s->st[pi].pln[ci].cmd != NULL)
			free(s->st[pi].pln[ci].cmd);
		s->st[pi].pln[ci].cmd = NULL;
		ci++;
	}
	free(s->st[pi].pln);
}

void	clear_fd_arr(t_set *s, int pi)
{
	if (s->st[pi].fd_arr != NULL)
		ft_free_int(s->st[pi].fd_arr);
}

void	clear_pid_arr(t_set *s, int pi)
{
	if (s->st[pi].pid_arr != NULL)
		free(s->st[pi].pid_arr);
	pi++;
}

void	clear_s(t_set *s)
{
	int		pi;

	pi = 0;
	while (pi < s->pn)
	{
		clear_st(s, pi);
		clear_fd_arr(s, pi);
		clear_pid_arr(s, pi);
		pi++;
	}
	free(s->st);
}
