/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:02 by rburton           #+#    #+#             */
/*   Updated: 2021/04/30 13:57:34 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_exc_arr(t_set *s, int si, int pi)
{
	int		i;
	char 	**exc_arr;

	exc_arr = (char**)malloc((s->set[si].ppline[pi].n + 1) * sizeof(char*));
	exc_arr[0] = s->argv0;
	i = 1;
	while (i < s->set[si].ppline[pi].n)
	{
		exc_arr[i] = s->set[si].ppline[pi].cmnd[i];
		i++;
	}
	exc_arr[i] = NULL;
	return (exc_arr);
}

void	complete_pth(char **pth, t_set *s, int si, int pi)
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
		pth[i] = ft_strjoin(pth[i], s->set[si].ppline[pi].cmnd[0]);
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

void	cmnd_node(t_set *s, int si, int pi)
{
    (void)s;
    printf("cmnd_node has reached\n");

    pid_t   pid;
	char	**exc_arr;
	char	**pth;
	char	*true_path;

	exc_arr = make_exc_arr(s, si, pi);
	print2darr(exc_arr, 0);
	pth = split_path(s);
	complete_pth(pth, s, si, pi);
	print2darr(pth, 0);
	true_path = path_checker(pth);
	printf("true_path: %s\n", true_path);
	pid = fork();
	if (pid == 0)
	{
		execve(true_path, exc_arr, s->env);
	}
	else
	{
		wait(&pid);
	}
}