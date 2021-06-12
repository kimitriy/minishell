/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdrct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:19:44 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 23:07:39 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rdrct_fd_fw(t_set *s)
{
	int	dup2rv_0;
	int	dup2rv_1;

	if (s->dol.fd_in != -2)
	{
		dup2rv_0 = dup2(s->dol.fd_in, 0);
		dup2protection(dup2rv_0);
	}
	if (s->dol.fd_out != -2)
	{
		dup2rv_1 = dup2(s->dol.fd_out, 1);
		dup2protection(dup2rv_1);
	}
}

void	rdrct_fd_rw(t_set *s)
{
	int	dup2rv_0;
	int	dup2rv_1;

	if (s->dol.fd_in != -2)
	{
		dup2rv_0 = dup2(s->fd_stdin, 0);
		dup2protection(dup2rv_0);
		close(s->dol.fd_in);
	}
	if (s->dol.fd_out != -2)
	{
		dup2rv_1 = dup2(s->fd_stdout, 1);
		dup2protection(dup2rv_1);
		close(s->dol.fd_out);
	}
}
