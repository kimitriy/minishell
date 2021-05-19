/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltns.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:54:12 by rburton           #+#    #+#             */
/*   Updated: 2021/05/20 01:39:53 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	bltn_echo(t_set *s, int pi, int ci)
{
	//проверить валидность -n (-nnnnn -nn (-nnnnnnnf - аргумент))
	//echo #xxx
	//echo ~
	
	int		len;

	if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[1], "-n"))
	{
		len = ft_strlen(s->st[pi].pln[ci].cmd[2]);
		write(1, s->st[pi].pln[ci].cmd[2], len);
	}
	else
	{
		len = ft_strlen(s->st[pi].pln[ci].cmd[1]);
		write(1, s->st[pi].pln[ci].cmd[1], len);
		write(1, "\n", 1);
	}
}

void	bltn_pwd()
{
	//переписать под write
	char	*path;

	path = getcwd(NULL, 0);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	// printf("%s\n", path);
}

void	bltn_env(t_set *s, int pi, int ci)
{
	//после unset path ничего не печатать и вывести ошибку bash: env: No such file or directory 127
	int		i;

	char	**path_key;
	path_key = key_in_arr(s->env, "PATH");
	if (NULL == path_key)
		err_no_such_file_or_directory(s, pi, ci);
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

void	bltn_exit()
{
	exit(0);
}

void	bltn_node(t_set *s, int pi, int ci)
{
	
	if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "echo"))
		bltn_echo(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "cd"))
		bltn_cd(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "pwd"))
		bltn_pwd();
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "export"))
		bltn_export(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "unset"))
		bltn_unset(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "env"))
		bltn_env(s, pi, ci);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "exit"))
		bltn_exit();
}