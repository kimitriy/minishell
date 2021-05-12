/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:03:31 by rburton           #+#    #+#             */
/*   Updated: 2021/05/11 18:51:51 by rburton          ###   ########.fr       */
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

void	err_cmnd_not_fnd(t_set *s, int pi, int ci)
{
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "command not found",  17);
	write(1, "\n", 1);
}

void	err_not_a_valid_id(t_set *s, int pi, int ci)
{
	s->err = 1;
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, s->st[pi].pln[ci].cmd[1], ft_strlen(s->st[pi].pln[ci].cmd[1]));
	write(1, ": ", 2);
	write(1, "not a valid identifier",  22);
	write(1, "\n", 1);
}