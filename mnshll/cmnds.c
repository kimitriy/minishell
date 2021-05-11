/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:02 by rburton           #+#    #+#             */
/*   Updated: 2021/05/11 01:32:28 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	complete_pth(char **pth, t_set *s, int pi, int ci)
{
	int		i;

	i = 0;
	while (NULL != pth[i])
	{
		pth[i] = ft_strjoin(pth[i], "/");
		i++;
	}
	i = 0;
	while (NULL != pth[i])
	{
		pth[i] = ft_strjoin(pth[i], s->set[pi].ppln[ci].cmnd[0]);
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

void	single_cmnd_node(t_set *s, int pi, int ci)
{
    (void)s;

	pid_t   pid;
	char	**pth;
	char	*true_path;

	pth = split_path(s);
	complete_pth(pth, s, pi, ci);
	true_path = path_checker(pth);
	if (true_path != NULL)
	{
		pid = fork();
		if (pid == 0)
			// execve(true_path, exc_arr, s->env);
			execve(true_path, s->set[pi].ppln[ci].cmnd, s->env);
		else
			wait(&pid);
	}
	else
	{
		err_cmnd_not_fnd(s, pi, ci);
	}
}

int		rvrs_indx(t_set *s, int pi, int ci)
{
	int		rv;

	rv = s->set[pi].cn - ci - 1;
	return (rv);
}

void	mltple_cmnd_node(t_set *s, int pi, int ci)
{
	char	**pth;
	char	*true_path;

	pth = split_path(s);
	complete_pth(pth, s, pi, ci);
	true_path = path_checker(pth);
	if (true_path != NULL)
	{
		execve(true_path, s->set[pi].ppln[ci].cmnd, s->env);
	}
	else
	{
		err_cmnd_not_fnd(s, pi, ci);
		write(1, "err", 3);
	}
}