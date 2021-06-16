/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:02 by rburton           #+#    #+#             */
/*   Updated: 2021/06/16 01:50:35 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rvrs_indx(t_set *s, int pi, int ci)
{
	int		rv;

	rv = s->st[pi].cn - ci - 1;
	return (rv);
}

void	mltple_cmd_node(t_set *s, int pi, int ci)
{
	char	**pth;
	char	*true_path;

	pth = split_path(s);
	complete_pth(pth, s, pi, ci);
	true_path = path_checker(pth);
	if (true_path != NULL)
		execve(true_path, s->st[pi].pln[ci].cmd, s->env);
	else
		err_cmnd_not_fnd(s, pi, ci);
}
