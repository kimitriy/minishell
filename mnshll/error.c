/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:03:31 by rburton           #+#    #+#             */
/*   Updated: 2021/06/03 13:02:53 by rburton          ###   ########.fr       */
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

void	err_cmnd_not_fnd(t_set *s, int pi, int ci)
{
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "command not found\n",  18);
	g_exit = 127;
}

void	err_not_a_valid_id(t_set *s, int pi, int ci)
{
	g_exit = 1;
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, s->st[pi].pln[ci].cmd[1], ft_strlen(s->st[pi].pln[ci].cmd[1]));
	write(1, ": ", 2);
	write(1, "not a valid identifier\n",  23);
	g_exit = 1;
}

void	err_home_not_set(t_set *s, int pi, int ci)
{
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "HOME not set\n",  13);
	g_exit = 1;
}

void	err_oldpwd_not_set(t_set *s, int pi, int ci)
{
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "OLDPWD not set\n",  15);
	g_exit = 1;
}

void	err_no_such_file_or_directory(t_set *s, int pi, int ci) //cd
{
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "No such file or directory\n",  26);
	g_exit = 1;
}

void	err_no_such_file_or_directory_env(t_set *s, int pi, int ci) //cd
{
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "No such file or directory\n",  26);
	g_exit = 127;
}

void	err_numeric_arg_required(t_set *s, int pi, int ci) //exit
{
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "numeric argument required\n",  26);
	g_exit = 255;
	exit(255);
}

void	err_too_many_arguments(t_set *s, int pi, int ci) //exit
{
	write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, "too many argumnents\n",  20);
	g_exit = 1;
}

void	err_permission_denied(t_set *s, int pi, int ci) //exit
{
	// write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, s->st[pi].pln[ci].cmd[1], ft_strlen(s->st[pi].pln[ci].cmd[1]));
	write(1, ": ", 2);
	write(1, "Permission denied\n",  18);
	g_exit = 1;
}

void	err_is_a_directory(t_set *s, int pi, int ci) //exit
{
	// write(1, "minishell: ",  11);
	write(1, s->st[pi].pln[ci].cmd[0], ft_strlen(s->st[pi].pln[ci].cmd[0]));
	write(1, ": ", 2);
	write(1, s->st[pi].pln[ci].cmd[1], ft_strlen(s->st[pi].pln[ci].cmd[1]));
	write(1, ": ", 2);
	write(1, "Is a directory\n",  15);
	g_exit = 1;
}