/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:02 by rburton           #+#    #+#             */
/*   Updated: 2021/06/06 20:19:12 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	complete_pth(char **pth, t_set *s, int pi, int ci)
{
	int		i;
	char	*tmp;

	i = 0;
	while (NULL != pth[i])
	{
		tmp = pth[i];
		pth[i] = ft_strjoin(pth[i], "/");
		free(tmp);
		i++;
	}
	i = 0;
	while (NULL != pth[i])
	{
		tmp = pth[i];
		pth[i] = ft_strjoin(pth[i], s->st[pi].pln[ci].cmd[0]);
		free(tmp);
		i++;
	}
}

char	**split_path(t_set *s)
{
	int		i;
	char	*str;
	char	**pth;

	i = 0;
	while (i < s->en)
	{
		if (NULL != ft_strnstr(s->env[i], "PATH=", 5))
		{
			str = ft_strtrim(s->env[i], "PATH=");
			pth = ft_split(str, ':');
			free(str);
		}
		i++;
	}
	return (pth);
}

char	*path_checker(char **pth)
{
	int			i;
	int			res;
	struct stat	buf;

	i = 0;
	while (NULL != pth[i])
	{
		res = stat(pth[i], &buf);
		if (res == 0 && (buf.st_mode & X_OK))
			return (pth[i]);
		i++;
	}
	return (NULL);
}

void	process_launcher(t_set *s, int pi, int ci, char **path)
{
	char	*true_path;
	pid_t   pid;
	int		status;

	true_path = path_checker(path);
	if (true_path != NULL)
	{
		pid = fork();
		if (pid == 0)
			execve(true_path, s->st[pi].pln[ci].cmd, s->env);
		else
		{
			wait(&status);
			g_exit = WEXITSTATUS(status);
		}
	}
	else
		err_cmnd_not_fnd(s, pi, ci);
}

void	single_cmd_node(t_set *s, int pi, int ci)
{
	char	**path;

	path = split_path(s);
	complete_pth(path, s, pi, ci);
	process_launcher(s, pi, ci, path);
	ft_free_str(path);
}

int		rvrs_indx(t_set *s, int pi, int ci)
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