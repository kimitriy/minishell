/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:02 by rburton           #+#    #+#             */
/*   Updated: 2021/05/06 23:13:23 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_exc_arr(t_set *s, int pi, int ci)
{
	int		i;
	char 	**exc_arr;

	exc_arr = (char**)malloc((s->set[pi].ppline[ci].n + 1) * sizeof(char*));
	exc_arr[0] = s->argv0;
	i = 1;
	while (i < s->set[pi].ppline[ci].n)
	{
		exc_arr[i] = s->set[pi].ppline[ci].cmnd[i];
		i++;
	}
	exc_arr[i] = NULL;
	return (exc_arr);
}

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
		pth[i] = ft_strjoin(pth[i], s->set[pi].ppline[ci].cmnd[0]);
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
	char	**exc_arr;
	char	**pth;
	char	*true_path;

	exc_arr = make_exc_arr(s, pi, ci);
	// print2darr(exc_arr, 0);
	pth = split_path(s);
	complete_pth(pth, s, pi, ci);
	// print2darr(pth, 0);
	true_path = path_checker(pth);
	// printf("true_path: %s\n", true_path);
	if (true_path != NULL)
	{
		pid = fork();
		if (pid == 0)
			execve(true_path, exc_arr, s->env);
		else
			wait(&pid);
	}
	else
	{
		err_cmnd_not_fnd(s, pi, ci);
	}
}

void	mltple_cmnd_node(t_set *s, int pi, int ci)
{
	char	**exc_arr;
	char	**pth;
	char	*true_path;
	
	exc_arr = make_exc_arr(s, pi, ci);
	pth = split_path(s);
	complete_pth(pth, s, pi, ci);
	true_path = path_checker(pth);
	if (true_path != NULL)
	{
		execve(true_path, exc_arr, s->env);
	}
	else
	{
		err_cmnd_not_fnd(s, pi, ci);
		write(1, "err", 3);
	}
}