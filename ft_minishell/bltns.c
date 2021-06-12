/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltns.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:54:12 by rburton           #+#    #+#             */
/*   Updated: 2021/06/11 22:07:27 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bltn_pwd(t_set *s)
{
	char	*path;
	char	**str;
	char	**prsd_str;

	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		free(path);
	}
	else
	{
		str = key_in_arr(s->env, "PWD");
		prsd_str = parse_arg(*str);
		write(1, prsd_str[1], ft_strlen(prsd_str[1]));
		write(1, "\n", 1);
		ft_free_str(prsd_str);
	}
}

void	bltn_env(t_set *s, int pi, int ci)
{
	int		i;
	char	**path_key;

	path_key = key_in_arr(s->env, "PATH");
	if (NULL == path_key)
		err_no_such_file_or_directory_env(s, pi, ci);
	else
	{
		i = 0;
		while (i < s->en)
		{
			if (NULL != ft_strchr(s->env[i], 61))
			{
				write(1, s->env[i], ft_strlen(s->env[i]));
				write(1, "\n", 1);
			}
			i++;
		}
	}
}

int	is_number(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (0 == ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	bltn_exit(t_set *s, int pi, int ci)
{
	if (s->st[pi].pln[ci].cmd[1] != NULL)
	{
		if (1 == is_number(s->st[pi].pln[ci].cmd[1]))
		{
			if (s->st[pi].pln[ci].n > 2)
				err_too_many_arguments(s, pi, ci);
			else
				exit(0);
		}
		else
			err_numeric_arg_required(s, pi, ci);
	}
	else
		exit(0);
}

void	bltn_node(t_set *s, int pi, int ci)
{
	if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "echo"))
		bltn_echo(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "cd"))
		bltn_cd(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "pwd"))
		bltn_pwd(s);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "export"))
		bltn_export(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "unset"))
		bltn_unset(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "env"))
		bltn_env(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "exit"))
		bltn_exit(s, pi, ci);
	rdrct_fd_rw(s);
}
