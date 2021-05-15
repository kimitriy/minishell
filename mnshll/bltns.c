/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltns.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:54:12 by rburton           #+#    #+#             */
/*   Updated: 2021/05/15 12:43:14 by rburton          ###   ########.fr       */
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



// void	bltn_pwd(t_set *s)
// {
// 	int		i;

// 	i = 0;
// 	while (i < s->en)
// 	{
// 		// printf("s->env[%d]: %s\n", i, s->env[i]);
// 		if (NULL != ft_strnstr(s->env[i], "PWD=", 4))
// 			printf("%s\n", ft_strtrim(s->env[i], "PWD="));
// 		i++;
// 	}
// }

void	bltn_pwd()
{
	//переписать под write
	char	*path;

	path = getcwd(NULL, 0);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	// printf("%s\n", path);
}

// void	bltn_export(t_set *s, int pi, int ci)
// {
// 	printf("export arg: %s\n", s->st[pi].pln[ci].cmd[1]);
	
// 	char	*rvno;
// 	char	*str;
// 	int		len;
// 	int		i;

// 	len = ft_strlen(s->st[pi].pln[ci].cmd[1]);
// 	rvno = ft_strchr(s->st[pi].pln[ci].cmd[1], 61);
// 	str = str_in_arr(s->exp, s->st[pi].pln[ci].cmd[1]);
// 	if (NULL == rvno)
// 	{
// 		//add to the export arr
// 		if (NULL == str)
// 		{
// 			ft_realloc(s->exp, s->exn, s->exn + 1, s->st[pi].pln[ci].cmd[1]);
// 		}
// 	}
// 	else
// 	{
// 		//check +=
// 		if (--rvno == 43)
// 		{
// 			//strjoin
// 		}
// 		else
// 		{
// 			str = NULL;
// 			str = (char*)malloc(1 * sizeof(char));
// 			str = ft_strjoin(str, s->st[pi].pln[ci].cmd[1]);
// 		}
// 	}

// 	print2darr(s->exp, 1);
// }

// void 	bltn_unset()
// {
	
// }

void	bltn_env(t_set *s)
{
	//после unset path ничего не печаттать и вывести ошибку bash: env: No such file or directory 127
	print2darr(s->env, 0);
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
		bltn_env(s);
	else if (0 == ft_strcmp(s->st[pi].pln[ci].cmd[0], "exit"))
		bltn_exit();
}