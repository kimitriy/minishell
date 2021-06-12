/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:03:31 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 22:26:20 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_message(char *error)
{
	write(1, "Error!\n", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	exit(1);
}

void	err_memory_allocation_error(void)
{
	write(1, "Memory allocation error!\n", 25);
	g_exit = 2;
	exit(2);
}

void	err_cmnd_not_fnd(t_set *s, int pi, int ci)
{
	write(1, "minishell: ", 11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "command not found\n", 18);
	g_exit = 127;
}

void	err_not_a_valid_id(t_set *s, int pi, int ci, int i)
{
	write(1, "minishell: ", 11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, s->st[pi].pln[ci].cmd[i], ft_strlen(s->st[pi].pln[ci].cmd[i]));
	write(1, ": ", 2);
	write(1, "not a valid identifier\n", 23);
	g_exit = 1;
}

void	err_home_not_set(t_set *s, int pi, int ci)
{
	write(1, "minishell: ", 11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "HOME not set\n", 13);
	g_exit = 1;
}
