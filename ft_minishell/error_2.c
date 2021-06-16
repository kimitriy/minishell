/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:03:31 by rburton           #+#    #+#             */
/*   Updated: 2021/06/16 04:22:24 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_oldpwd_not_set(t_set *s, int pi, int ci)
{
	write(1, "minishell: ", 11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "OLDPWD not set\n", 15);
	g_exit = 1;
}

void	err_no_such_file_or_directory(t_set *s, int pi, int ci)
{
	write(1, "minishell: ", 11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "No such file or directory\n", 26);
	g_exit = 127;
}

void	err_no_such_file_or_directory_env(t_set *s, int pi, int ci)
{
	write(1, "minishell: ", 11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "No such file or directory\n", 26);
	g_exit = 127;
}

void	err_numeric_arg_required(t_set *s, int pi, int ci)
{
	write(1, "minishell: ", 11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "numeric argument required\n", 26);
	g_exit = 258;
	exit(258);
}

void	err_too_many_arguments(t_set *s, int pi, int ci)
{
	write(1, "minishell: ", 11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "too many argumnents\n", 20);
	g_exit = 258;
}
