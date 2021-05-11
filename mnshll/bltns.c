/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltns.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:54:12 by rburton           #+#    #+#             */
/*   Updated: 2021/05/11 02:09:38 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_path(t_set *s, int pi, int ci)
{
	int		i;
	char	*path;

	if (s->set[pi].ppln[ci].cmnd[1] != NULL)
	{
		path = (char*)malloc((ft_strlen(s->set[pi].ppln[ci].cmnd[1]) + 1) * sizeof(char));
		if (NULL == path)
			return (NULL);
		ft_strcpy(path, s->set[pi].ppln[ci].cmnd[1]);
	}
	else
	{
		i = 0;
		while (i < s->en)
		{
			if (NULL != ft_strnstr(s->env[i], "HOME=", 5))
			{	
				path = (char*)malloc((ft_strlen(s->env[i]) + 1) * sizeof(char));
				ft_strcpy(path, s->env[i]);
				path = ft_strtrim(path, "HOME=");
			}
			i++;
		}
	}
	return (path);
}

void	bltn_echo(t_set *s, int pi, int ci)
{
	int		len;

	if (0 == ft_strcmp(s->set[pi].ppln[ci].cmnd[1], "-n"))
	{
		len = ft_strlen(s->set[pi].ppln[ci].cmnd[2]);
		write(1, s->set[pi].ppln[ci].cmnd[2], len);
	}
	else
	{
		len = ft_strlen(s->set[pi].ppln[ci].cmnd[1]);
		write(1, s->set[pi].ppln[ci].cmnd[1], len);
		write(1, "\n", 1);
	}
}

void	bltn_cd(t_set *s, int pi, int ci)
{
	int		err_num;
	int		chdir_err;
	char	*path;

	errno = 0;
	path = set_path(s, pi, ci);
	chdir_err = chdir(path);
	if (chdir_err != 0)
	{
		err_num = errno;
		printf("%s", strerror(err_num));
	}
	
	bltn_pwd(s);
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
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
}

void	bltn_export(t_set *s, int pi, int ci)
{
	printf("export arg: %s\n", s->set[pi].ppln[ci].cmnd[1]);
	
	char	*rvno;
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(s->set[pi].ppln[ci].cmnd[1]);
	rvno = ft_strchr(s->set[pi].ppln[ci].cmnd[1], 61);
	str = str_in_arr(s->exp, s->set[pi].ppln[ci].cmnd[1]);
	if (NULL == rvno)
	{
		//add to the export arr
		if (NULL == str)
		{
			ft_realloc(s->exp, s->exn, s->exn + 1, s->set[pi].ppln[ci].cmnd[1]);
		}
	}
	else
	{
		//check +=
		if (--rvno == 43)
		{
			//strjoin
		}
		else
		{
			str = NULL;
			str = (char*)malloc(1 * sizeof(char));
			str = ft_strjoin(str, s->set[pi].ppln[ci].cmnd[1]);
		}
	}

	print2darr(s->exp, 1);
}

// void 	bltn_unset()
// {
	
// }

void	bltn_env(t_set *s)
{
	
	print2darr(s->env, 0);
}

void	bltn_exit()
{
	exit(0);
}

void	bltn_node(t_set *s, int pi, int ci)
{
	
	if (0 == ft_strcmp(s->set[pi].ppln[ci].cmnd[0], "echo"))
		bltn_echo(s, pi, ci);
	else if (0 == ft_strcmp(s->set[pi].ppln[ci].cmnd[0], "cd"))
		bltn_cd(s, pi, ci);
	else if (0 == ft_strcmp(s->set[pi].ppln[ci].cmnd[0], "pwd"))
		bltn_pwd();
	else if (0 == ft_strcmp(s->set[pi].ppln[ci].cmnd[0], "export"))
		bltn_export(s, pi, ci);
	else if (0 == ft_strcmp(s->set[pi].ppln[ci].cmnd[0], "unset"))
		printf("unset\n");
	else if (0 == ft_strcmp(s->set[pi].ppln[ci].cmnd[0], "env"))
		bltn_env(s);
	else if (0 == ft_strcmp(s->set[pi].ppln[ci].cmnd[0], "exit"))
		bltn_exit();
}